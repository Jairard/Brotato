#ifndef __POT_DNA_COLLECTOR__
#define __POT_DNA_COLLECTOR__

#include <utility>
#include <limits>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include "Core/Singleton.hpp"
#include "Core/NonCopyable.hpp"
#include "Core/Tools.hpp"
#include "Core/types.hpp"
#include "Debug/assert.hpp"
#include "Debug/Logger.hpp"

// TODO:
// - checkIntegrity
// - callstack
// - abstract timestamp handling
// - file .tpl
// - pool for [Organism|DNA]Info ?
// - check integrity ptr <-> type_info ?
// - size()

/*
 * Complexity notations:
 * - OrgC: organism count. If a pointer has several timestamps, they are included.
 * - OrgWC: organisms weak count. If a pointer has several timestamps, it counts as 1.
 * - TC: timestamp count. Number of timestamps for the current organism.
 * - DnaC: dna count. If a timestamp as several dnas per type, each of them counts as 1.
 * - DnaWC: dna weakn count. If a timestamp as several dnas per type, it counts as 1.
 * - DnaTC: dna type count. Number of different dna types for the current timestamp.
 * - DnaCTC: dna current timestamp count. Number of dnas for the current timestamp.
 * - O(v1) | O(v2) / O(v3) | O(v4): amortized complexity in release | debug / worst case complexity in release | debug.
 *
 * For readability, approximations O(OrgWC) + O(TC) = O(OrgC) and O(DnaWC) + O(DnaTC) = O(DnaC) may be done.
 */
namespace Pot
{
	namespace Debug
	{
		class Logger;
	}
	
	template <typename OrganismType>
	class DNA;

	using Debug::Logger;

	class DNACollector: public Singleton<DNACollector>, public NonCopyable
	{
		template <typename T>
		friend class Singleton;
		template <typename T>
		friend class DNA;
		friend class BaseOrganism;

	protected:
		DNACollector();
		virtual ~DNACollector();

	public:
		static void dump(const char* tag);

	private:
		/* Release:                O(1) / O(OrgWC) + O(DnaWC) */
		/* Debug:   O(OrgWC) + O(DnaWC) / O(OrgC)  + O(DnaWC) */
		template <typename OrganismType>
		void registerDNA(DNA<OrganismType>& dna);
		
		/* O(DnaTC) / O(DnaC) + O(OrgWC) | O(DnaC) * O(OrgC) */
		template <typename OrganismType>
		void unregisterDNA(const DNA<OrganismType>& dna);

		/* O(DnaCTC) / O(OrgC) + O(DnaCTC) */
		template <typename OrganismType>
		void notifyOrganismDeath(const OrganismType& organism);

		void dump_internal(const char* tag) const;

	private:
		typedef potu64 Timestamp;

		struct DNAInfo
		{
			const void* ptr;
			const void* organism;
			void** organismPtr;
#ifdef POT_DEBUG
			const char* callstack;
#endif

			DNAInfo();
		};

		struct OrganismInfo
		{
			const void* ptr;
#ifdef POT_DEBUG
			bool alive; // Debug only
			const std::type_info& type; // Debug only
			const char* callstack; // Debug only
#endif

			OrganismInfo();
			OrganismInfo(const void* _ptr, const std::type_info& _type, bool _alive = true);
		};

		// DNA container
		typedef std::vector<DNAInfo> DNAList;
		typedef std::unordered_map<std::type_index, DNAList> DNAsByType;
		typedef std::unordered_map<Timestamp, DNAsByType> DNAContainer;

		// Organism container
		typedef std::unordered_map<Timestamp, OrganismInfo> OrganismByTimestamp;
		typedef std::pair<Timestamp, OrganismByTimestamp> OrganismsInfoForPointer; // Timestamp: aliveTimestamp
		typedef std::unordered_map<const void*, OrganismsInfoForPointer> OrganismContainer;

		static const Timestamp INVALID_TIMESTAMP = std::numeric_limits<Timestamp>::max();
		DNAContainer m_dnaContainer;
		OrganismContainer m_organismContainer;
		Timestamp m_timestamp;

		private:
			/* O(OrgC) */
			const OrganismInfo* getOrganismInfoFromTimestamp(const Timestamp& t) const;
			/* O(1) / O(OrgWC) | O(OrgC) */
			const Timestamp& createOrganismEntry(const void* ptr, const std::type_info& type);
			/* O(1) / O(OrgWC) | O(OrgC) */
			void clearOrganismInfoForTimestamp(const void* ptr, const Timestamp& t);
			/* Alive: O(1) / O(OrgWC) | O(OrgC) */
			/* Dead:  O(DnaC) | O(DnaC) * O(OrgC) */
			Timestamp fetchTimestamp(const void* dnaPtr, const std::type_index& dnaTypeIndex, const void* organismPtr, const void** outOrganismPtr = nullptr);
			/* O(OrgWC) */
			size_t organismCount() const;
			/* O(DnaC) */
			size_t dnaCount() const;

#ifdef POT_DEBUG
			/* O(1) / O(OrgC) */
			void checkOrganismStatus(const void* ptr, const Timestamp& t, bool shouldBeAlive); // Debug only
#endif
	};

	/* Release:                O(1) / O(OrgWC) + O(DnaWC) */
	/* Debug:   O(OrgWC) + O(DnaWC) / O(OrgC)  + O(DnaWC) */
	template <typename OrganismType>
	void DNACollector::registerDNA(DNA<OrganismType>& dna)
	{
		// Create info structure and fill it
		DNAInfo dnaInfo;
		dnaInfo.ptr = reinterpret_cast<const void*>(&dna);
		dnaInfo.organism = reinterpret_cast<const void*>(dna.m_organism);
		dnaInfo.organismPtr = reinterpret_cast<void**>(&dna.m_organism);
#ifdef POT_DEBUG
		dnaInfo.callstack = nullptr;
#endif

		/* Fetch the corresponding timestamp */
		Timestamp t = INVALID_TIMESTAMP;
		OrganismContainer::iterator organismIt = m_organismContainer.find(dnaInfo.organism); /* O(1) / O(OrgWC) */
		/* O(1) / O(OrgWC) | O(OrgC) */
		if (organismIt == m_organismContainer.end() ||     // There is no entry for this organism OR
		    organismIt->second.first == INVALID_TIMESTAMP) // there is already an entry by it's dead
		                                                   // (may occur with pools or other reallocation at the same adress)
		{
			t = createOrganismEntry(dnaInfo.organism, typeid(OrganismType)); /* O(1) / O(OrgWC) | O(OrgC) */
		}
		else
		{
			const Timestamp& aliveTimestamp = organismIt->second.first;
			ASSERT_DEBUG(aliveTimestamp != INVALID_TIMESTAMP);
			ASSERT_DEBUG(m_dnaContainer.find(aliveTimestamp) != m_dnaContainer.end());

#ifdef POT_DEBUG
			OrganismByTimestamp& organisms = organismIt->second.second;
			ASSERT_DEBUG(organisms.find(aliveTimestamp) != organisms.end()); /* O(1) / O(TC) */
			ASSERT_DEBUG(organisms[aliveTimestamp].alive); /* O(1) / O(TC) */
#endif
			t = aliveTimestamp;
		}
		ASSERT_DEBUG(t != INVALID_TIMESTAMP);

		// Add the data to the container
		std::type_index dnaTypeIndex = std::type_index(typeid(DNA<OrganismType>));
		m_dnaContainer[t][dnaTypeIndex].push_back(dnaInfo); /* O(1) / O(DnaWC) */

		Logger::log(Logger::CWarning, "Added, there is(are) %d dna(s) for the same organism and type", m_dnaContainer[t][dnaTypeIndex].size());
		Logger::log(Logger::CWarning, "organismCount(%u), dnaCount(%u), timestamp(%llu)", m_organismContainer.size(), m_dnaContainer.size(), t);
		
		ASSERT_DEBUG(organismCount() == m_dnaContainer.size()); /* O(OrgWC) + O(DnaWC) */
	}

	/* O(DnaTC) / O(DnaC) + O(OrgWC) | O(DnaC) * O(OrgC) */
	template <typename OrganismType>
	void DNACollector::unregisterDNA(const DNA<OrganismType>& dna)
	{
		const void* dnaPtr = reinterpret_cast<const void*>(&dna);
		const void* organism = reinterpret_cast<const void*>(dna.m_organism);
		const std::type_index dnaTypeIndex(typeid(DNA<OrganismType>));

		/* Alive: O(1) / O(OrgWC) | O(OrgC) */
		/* Dead:  O(DnaC) | O(DnaC) * O(OrgC) */
		Timestamp t = fetchTimestamp(dnaPtr, dnaTypeIndex, organism, &organism);
		ASSERT_DEBUG(m_dnaContainer.find(t) != m_dnaContainer.end()); /* O(1) / O(DnaWC) */
		DNAsByType& dnas = m_dnaContainer[t]; /* O(1) / O(DnaWC) */
		ASSERT_DEBUG(dnas.find(dnaTypeIndex) != dnas.end()); /* O(1) / O(DnaTC) */
		DNAList& typedDnas = dnas[dnaTypeIndex]; /* O(1) / O(DnaTC) */

#ifdef POT_DEBUG
		bool found = false;
#endif
		/* O(DnaTC) */
		for (DNAList::iterator it = typedDnas.begin(); it != typedDnas.end(); ++it)
		{
			if (it->ptr == dnaPtr)
			{
				typedDnas.erase(it);
#ifdef POT_DEBUG
				found = true;
#endif
				break;
			}
		}

#ifdef POT_DEBUG
		ASSERT_DEBUG(found);
#endif

		if (typedDnas.empty())
			dnas.erase(dnaTypeIndex); /* O(1) / O(DnaTC) */
		if (dnas.empty())
		{
			m_dnaContainer.erase(t); /* O(1) / O(DnaWC) */
			clearOrganismInfoForTimestamp(organism, t); /* O(1) / O(OrgWC) | O(OrgC) */
		}
	}

	/* O(DnaCTC) / O(OrgC) + O(DnaCTC) */
	template <typename OrganismType>
	void DNACollector::notifyOrganismDeath(const OrganismType& organism)
	{
		const void* ptr = reinterpret_cast<const void*>(&organism);
		OrganismContainer::iterator containerIt = m_organismContainer.find(ptr); /* O(1) / O(OrgWC) */
		if (containerIt == m_organismContainer.end()) // No references on this pointer
			return;

		// Clearing alive info
		OrganismsInfoForPointer& infoForPtr = containerIt->second;
		Timestamp& aliveTimestampRef = infoForPtr.first;
#ifdef POT_DEBUG
		OrganismByTimestamp& organisms = infoForPtr.second;
		ASSERT_DEBUG(organisms.find(aliveTimestampRef) != organisms.end()); /* O(1) / O(OrgTC) */
		OrganismInfo& aliveInfo = organisms[aliveTimestampRef]; /* O(1) / O(OrgTC) */
		ASSERT_DEBUG(aliveInfo.alive);
		aliveInfo.alive = false;
#endif
		Timestamp t = aliveTimestampRef;
		ASSERT_DEBUG(t != INVALID_TIMESTAMP);
		aliveTimestampRef = INVALID_TIMESTAMP;

		// all the info should be dead now
#ifdef POT_DEBUG
		/* O(OrgTC) */
		for (OrganismByTimestamp::const_iterator organismsIt = organisms.begin(); organismsIt != organisms.end(); ++organismsIt)
		{
			const OrganismInfo& info = organismsIt->second;
			ASSERT_DEBUG(!info.alive);
		}
#endif

		DNAContainer::iterator dnaIt = m_dnaContainer.find(t); /* O(1) / O(DnaWC) */
		if (dnaIt == m_dnaContainer.end()) // No dna for this organism
			return;

		/* O(DnaCTC) */
		DNAsByType& dnas = dnaIt->second;
		for (DNAsByType::iterator dnasByTypeIt = dnas.begin(); dnasByTypeIt != dnas.end(); ++dnasByTypeIt)
		{
			DNAList& typedDnas = dnasByTypeIt->second;
			for (DNAList::iterator typedIt = typedDnas.begin(); typedIt != typedDnas.end(); ++typedIt)
			{
				DNAInfo& info = *typedIt;
				ASSERT_RELEASE(info.organismPtr != nullptr);
				ASSERT_DEBUG(*info.organismPtr != nullptr);
				*info.organismPtr = nullptr;
			}
		}
	}
}

#endif
