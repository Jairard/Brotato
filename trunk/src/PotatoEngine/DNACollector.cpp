#include "stdafx.h"
#include "DNACollector.hpp"

#include <set>
#include <utility>
#include <sstream>
#include "Debug/Logger.hpp"
#include "Debug/Demangler.hpp"
#include "BaseDNA.hpp"
#include "BaseOrganism.hpp"

namespace Pot
{
	using Debug::Demangler;

	const char* DNACollector::c_tag = "DNACollector";

	// DNACollector::DNAInfo
	DNACollector::DNAInfo::DNAInfo(BaseDNA& _dna):
		  dna(_dna)
		, organism(nullptr)
#ifdef POT_DEBUG
		, callstack(nullptr)
#endif
	{}

	DNACollector::DNAInfo& DNACollector::DNAInfo::operator=(const DNAInfo& other)
	{
		dna = other.dna;
		organism = other.organism;
#ifdef POT_DEBUG
		// TODO: copy callstack
		callstack = other.callstack;
#endif

		return *this;
	}

	// DNACollector::OrganismInfo
	DNACollector::OrganismInfo::OrganismInfo():
		  ptr(nullptr)
#ifdef POT_DEBUG
		, alive(false)
		, type(typeid(void))
		, callstack(nullptr)
#endif
	{}

	DNACollector::OrganismInfo::OrganismInfo(const BaseOrganism* _ptr, const std::type_info& _type, bool _alive):
		  ptr(_ptr)
#ifdef POT_DEBUG
		, alive(_alive)
		, type(_type)
		, callstack(nullptr)
#endif
	{
#ifndef POT_DEBUG
		POT_UNUSED(_type);
		POT_UNUSED(_alive);
#endif
	}

	// DNACollector
	DNACollector::DNACollector():
		  m_dnaContainer()
		, m_organismContainer()
		, m_timestamp()
#ifdef POT_DEBUG
		, m_checker(*this)
#endif
	{
#ifdef POT_DEBUG
		checkIntegrityIFN();
#endif
	}

	DNACollector::~DNACollector()
	{
		ASSERT_DEBUG(m_dnaContainer.empty());
		ASSERT_DEBUG(m_organismContainer.empty());
	}
	
	void DNACollector::dump(const char* tag)
	{
		instance().dump_internal(tag);
	}

	void DNACollector::dump_internal(const char* tag) const
	{
		Logger::log(tag, "======== DNACollector dump ========");

		Logger::log(tag, "Current timestamp: %llu", m_timestamp.value());
		Logger::log(tag, "Organism count: %u", organismCount());
		Logger::log(tag, "Dna count: %U", dnaCount());

		if (!m_organismContainer.empty())
			Logger::log(tag, "");

		size_t ptrCount = m_organismContainer.size();
		Logger::log(tag, "Referenced organisms (for %u addess%s)", ptrCount, (ptrCount > 1 ? "es" : ""));
		for (OrganismContainer::const_iterator ptrIt = m_organismContainer.begin(); ptrIt != m_organismContainer.end(); ++ptrIt)
		{
			const BaseOrganism* ptr = ptrIt->first;
			const OrganismsInfoForPointer& infoForPtr = ptrIt->second;
			const DNACollectorTimestamp& aliveTimestamp = infoForPtr.first;
			const OrganismByTimestamp& organismsByTimestamp = infoForPtr.second;

			const size_t timestampCount = organismsByTimestamp.size();
			Logger::log(tag, "* Addess: %#p (%u timestamp%s)", ptr, timestampCount, (timestampCount > 1 ? "s" : ""));
			if (!aliveTimestamp.isValid())
				Logger::log(tag, "  Is alive with timestamp %llu", aliveTimestamp.value());
			else
				Logger::log(tag, "  Is not alive");

			size_t i = 0;
			for (OrganismByTimestamp::const_iterator organismIt = organismsByTimestamp.begin(); organismIt != organismsByTimestamp.end(); ++organismIt)
			{
				const DNACollectorTimestamp& t = organismIt->first;

				Logger::log(tag, "  [%3u] Timestamp: %llu", i, t.value());
#ifdef POT_DEBUG
				const OrganismInfo& info = organismIt->second;
				Logger::log(tag, "        Alive: %s", Tools::bool2str(info.alive));
				Logger::log(tag, "        Type: %s", Demangler(info.type)());
#endif
				++i;
			}
		}

		if (!m_dnaContainer.empty())
			Logger::log(tag, "");

		for (DNAContainer::const_iterator containerIt = m_dnaContainer.begin(); containerIt != m_dnaContainer.end(); ++containerIt)
		{
			const OrganismInfo& organismInfo = *getOrganismInfoFromTimestamp(containerIt->first);
			const DNAsByType& dnas = containerIt->second;

			size_t typeCount = dnas.size();
			Logger::log(tag, "DNAs registered for organism [%llu @ %#p] (in %u type%s):",
			                 containerIt->first.value(), organismInfo.ptr, typeCount, (typeCount > 1 ? "s" : ""));
			for (DNAsByType::const_iterator dnasIt = dnas.begin(); dnasIt != dnas.end(); ++dnasIt)
			{
				const std::type_index& type = dnasIt->first;
				const DNAList& typedDnas = dnasIt->second;

				const size_t dnaCount = typedDnas.size();
				Logger::log(tag, "* %s (%u element%s)", Demangler(type)(), dnaCount, (dnaCount > 1 ? "s" : ""));
				for (size_t i = 0; i < typedDnas.size(); ++i)
				{
					const DNAInfo& dnaInfo = typedDnas[i];
					Logger::log(tag, "  [%3u] Adress: %#p", i, &dnaInfo.dna);
					Logger::log(tag, "        organism: current(%#p), stored(%#p)", dnaInfo.dna.organism(), dnaInfo.organism);
					Logger::log(tag, "        timestamp: %llu", containerIt->first.value());
				}
			}
		}

		Logger::log(tag, "===================================");
	}

	const char* DNACollector::tag()
	{
		return c_tag;
	}

	size_t DNACollector::memorySize() const
	{
		size_t size = 0;
		const size_t timestampSize = sizeof(DNACollectorTimestamp);

		// m_dnaContainer
		size += sizeof(DNAContainer);
		for (DNAContainer::const_iterator containerIt = m_dnaContainer.begin(); containerIt != m_dnaContainer.end(); ++containerIt)
		{
			const DNAsByType& dnas = containerIt->second;
			size += timestampSize + sizeof(DNAsByType);

			for (DNAsByType::const_iterator dnasIt = dnas.begin(); dnasIt != dnas.end(); ++dnasIt)
			{
				size += sizeof(std::type_index) + sizeof(DNAList);
				size += sizeof(DNAInfo) * dnasIt->second.size();
			}
		}

		// m_organismContainer
		size += sizeof(OrganismContainer);
		for (OrganismContainer::const_iterator containerIt = m_organismContainer.begin(); containerIt != m_organismContainer.end(); ++containerIt)
		{
			const OrganismByTimestamp& organisms = containerIt->second.second;
			size += sizeof(const BaseOrganism*) + sizeof(OrganismsInfoForPointer);
			size += (timestampSize + sizeof(OrganismInfo)) * organisms.size();
		}

		size += timestampSize; // m_timestamp

		return size;
	}

	/* Release:                O(1) / O(OrgWC) + O(DnaWC) */
	/* Debug:   O(OrgWC) + O(DnaWC) / O(OrgC)  + O(DnaWC) */
	void DNACollector::registerDNA(BaseDNA& dna, const std::type_info& organismType)
	{
		Logger::log(c_tag, "register dna [%s @ %#p] for organism [%s @ %#p]",
		    Demangler(dna)(), &dna,
		    Demangler(organismType)(), dna.organism());

		// Create info structure and fill it
		DNAInfo dnaInfo(dna);
		dnaInfo.organism = dna.organism();
#ifdef POT_DEBUG
		dnaInfo.callstack = nullptr;
#endif

		const BaseOrganism* organism = dna.organism();

		/* Fetch the corresponding timestamp */
		DNACollectorTimestamp t = DNACollectorTimestamp::c_invalid;
		OrganismContainer::iterator organismIt = m_organismContainer.find(organism); /* O(1) / O(OrgWC) */
		/* O(1) / O(OrgWC) | O(OrgC) */
		if (organismIt == m_organismContainer.end() ||      // There is no entry for this organism OR
		    !organismIt->second.first.isValid())            // there is already an entry but it's dead
		                                                    // (may occur with pools or other reallocation at the same adress)
		{
			t = createOrganismEntry(organism, organismType); /* O(1) / O(OrgWC) | O(OrgC) */
		}
		else
		{
			const DNACollectorTimestamp& aliveTimestamp = organismIt->second.first;
			ASSERT_DEBUG(aliveTimestamp.isValid());
			ASSERT_DEBUG(m_dnaContainer.find(aliveTimestamp) != m_dnaContainer.end());

#ifdef POT_DEBUG
			OrganismByTimestamp& organisms = organismIt->second.second;
			ASSERT_DEBUG(organisms.find(aliveTimestamp) != organisms.end()); /* O(1) / O(TC) */
			ASSERT_DEBUG(organisms[aliveTimestamp].alive); /* O(1) / O(TC) */
#endif
			t = aliveTimestamp;
		}
		ASSERT_DEBUG(t.isValid());

		// Add the data to the container
		std::type_index dnaTypeIndex = std::type_index(typeid(dna));
		m_dnaContainer[t][dnaTypeIndex].push_back(dnaInfo); /* O(1) / O(DnaWC) */

		ASSERT_DEBUG(organismCount() == m_dnaContainer.size()); /* O(OrgWC) + O(DnaWC) */

#ifdef POT_DEBUG
		checkIntegrityIFN();
#endif
	}

	/* O(DnaTC) / O(DnaC) + O(OrgWC) | O(DnaC) * O(OrgC) */
	void DNACollector::unregisterDNA(BaseDNA& dna)
	{
		const BaseOrganism* organism = dna.organism();
		const std::type_index organismType = (organism != nullptr ? typeid(*organism) : typeid(organism));

		Logger::log(c_tag, "unregister dna [%s @ %#p] for organism [%s @ %#p]",
		    Demangler(dna)(), &dna,
		    Demangler(organismType)(), dna.organism());

		const std::type_index dnaTypeIndex(typeid(dna));

		/* Alive: O(1) / O(OrgWC) | O(OrgC) */
		/* Dead:  O(DnaC) | O(DnaC) * O(OrgC) */
		DNACollectorTimestamp t = fetchTimestamp(dna, dnaTypeIndex, &organism);
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
			if (&it->dna == &dna)
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

#ifdef POT_DEBUG
		checkIntegrityIFN();
#endif
	}

	/* O(DnaCTC) / O(OrgC) + O(DnaCTC) */
	void DNACollector::notifyOrganismDeath(const BaseOrganism& organism)
	{
		const BaseOrganism* organismPtr = &organism;
		OrganismContainer::iterator containerIt = m_organismContainer.find(organismPtr); /* O(1) / O(OrgWC) */

		std::type_index organismType = std::type_index(typeid(organism)); // No more polymorphism since it's called from base destructor
#ifdef POT_DEBUG
		// Trying to get the polymorphic type in debug
		if (containerIt != m_organismContainer.end())
		{
			const OrganismByTimestamp& organisms = containerIt->second.second; /* O(1) */
			if (!organisms.empty())
			{
				const OrganismInfo& info = organisms.begin()->second; /* O(1) */
				organismType = std::type_index(info.type);
			}
		}
#endif
		Logger::log(c_tag, "notify death of organism [%s @ %#p]", Demangler(organismType)(), &organism);

		if (containerIt == m_organismContainer.end()) // No references on this pointer
		{
#ifdef POT_DEBUG
			checkIntegrityIFN();
#endif
			return;
		}

		// Clearing alive info
		OrganismsInfoForPointer& infoForPtr = containerIt->second;
		DNACollectorTimestamp& aliveTimestampRef = infoForPtr.first;
#ifdef POT_DEBUG
		OrganismByTimestamp& organisms = infoForPtr.second;
		ASSERT_DEBUG(organisms.find(aliveTimestampRef) != organisms.end()); /* O(1) / O(OrgTC) */
		OrganismInfo& aliveInfo = organisms[aliveTimestampRef]; /* O(1) / O(OrgTC) */
		ASSERT_DEBUG(aliveInfo.alive);
		aliveInfo.alive = false;
#endif
		DNACollectorTimestamp t = aliveTimestampRef;
		ASSERT_DEBUG(t.isValid());
		aliveTimestampRef.invalidate();

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
		{
#ifdef POT_DEBUG
			checkIntegrityIFN();
#endif
			return;
		}

		/* O(DnaCTC) */
		DNAsByType& dnas = dnaIt->second;
		for (DNAsByType::iterator dnasByTypeIt = dnas.begin(); dnasByTypeIt != dnas.end(); ++dnasByTypeIt)
		{
			DNAList& typedDnas = dnasByTypeIt->second;
			for (DNAList::iterator typedIt = typedDnas.begin(); typedIt != typedDnas.end(); ++typedIt)
				typedIt->dna.onOrganismDeath(organismPtr);
		}

#ifdef POT_DEBUG
		checkIntegrityIFN();
#endif
	}

	/* O(OrgC) */
	const DNACollector::OrganismInfo* DNACollector::getOrganismInfoFromTimestamp(const DNACollectorTimestamp& t) const
	{
		for (OrganismContainer::const_iterator it = m_organismContainer.begin(); it != m_organismContainer.end(); ++it)
		{
			const OrganismByTimestamp& organisms = it->second.second;
			for (OrganismByTimestamp::const_iterator organismIt = organisms.begin(); organismIt != organisms.end(); ++organismIt)
			{
				if (organismIt->first == t)
					return &organismIt->second;
			}
		}

		ASSERT_NOT_REACHED();
		return nullptr;
	}

	/* O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
	const DNACollectorTimestamp& DNACollector::createOrganismEntry(const BaseOrganism* ptr, const std::type_info& type)
	{
		const DNACollectorTimestamp& t = m_timestamp++;

		OrganismsInfoForPointer& infoForPtr = m_organismContainer[ptr]; /* O(1) / O(OrgWC) */
		const bool isAlive = (ptr != nullptr);
		OrganismInfo organismInfo(ptr, type, isAlive);
		infoForPtr.second.insert(std::make_pair(t, organismInfo));

		DNACollectorTimestamp& aliveTimestamp = infoForPtr.first;
		aliveTimestamp = t;

#ifdef POT_DEBUG
		OrganismByTimestamp& organisms = infoForPtr.second;
		ASSERT_DEBUG(organisms.find(t) != organisms.end()); /* O(1) / O(TC) */
		ASSERT_DEBUG(organisms[t].alive == isAlive); /* O(1) / O(TC) */
#endif

		return	aliveTimestamp;
	}
	
	/* O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
	void DNACollector::clearOrganismInfoForTimestamp(const BaseOrganism* ptr, const DNACollectorTimestamp& t)
	{
		ASSERT_DEBUG(m_organismContainer.find(ptr) != m_organismContainer.end()); /* O(1) / O(OrgWC) */
		OrganismsInfoForPointer& infoForPtr = m_organismContainer[ptr]; /* O(1) / O(OrgWC) */

		OrganismByTimestamp& timestamps = infoForPtr.second;
		// Clearing a timestamp that is not registered
		ASSERT_DEBUG(timestamps.find(t) != timestamps.end()); /* O(1) / O(TC) */

		DNACollectorTimestamp& aliveTimestamp = infoForPtr.first;
		if (aliveTimestamp == t)
			aliveTimestamp.invalidate();
		
		timestamps.erase(t);
		if (timestamps.empty())
			m_organismContainer.erase(ptr); /* O(1) / O(OrgWC) */
	}

	/* Alive: O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
	/* Dead:  O(DnaC) | O(DnaC) * (O(OrgWC) + O(TC)) */
	DNACollectorTimestamp DNACollector::fetchTimestamp(const BaseDNA& dna, const std::type_index& dnaTypeIndex, const BaseOrganism** outOrganism) const
	{
		const BaseOrganism* organism = dna.organism();

		if (organism == nullptr) // Organism is dead, we have to fetch the organism ptr in the DNA container
		{
			const BaseDNA* dnaPtr = &dna;
			/* O(DnaC) | O(DnaC) * (O(OrgWC) + O(TC)) */
			for (DNAContainer::const_iterator containerIt = m_dnaContainer.begin(); containerIt != m_dnaContainer.end(); ++containerIt)
			{
				const DNACollectorTimestamp& t = containerIt->first;
				const DNAsByType& dnas = containerIt->second;
				DNAsByType::const_iterator dnaIt = dnas.find(dnaTypeIndex);
				if (dnaIt == dnas.end())
					continue;

				const DNAList typedDnas = dnaIt->second;
				for (DNAList::const_iterator it = typedDnas.begin(); it != typedDnas.end(); ++it)
				{
					if (&it->dna == dnaPtr)
					{
						if (outOrganism != nullptr)
							*outOrganism = it->organism;
						ASSERT_DEBUG(t.isValid());
#ifdef POT_DEBUG
						checkOrganismStatus(*outOrganism, t, false); /* O(1) / O(OrgWC) + O(TC) */
#endif
						return t;
					}
				}
			}

			ASSERT_NOT_REACHED();
			return DNACollectorTimestamp::c_invalid;
		}
		else // Organism is alive, we can directly look in the organism container
		{
			/* O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
			OrganismContainer::const_iterator it = m_organismContainer.find(organism); /* O(1) / O(OrgWC) */
			ASSERT_RELEASE(it != m_organismContainer.end());
			const OrganismsInfoForPointer& infoForPtr = it->second;
			const DNACollectorTimestamp& t = infoForPtr.first;
			ASSERT_DEBUG(t.isValid());

#ifdef POT_DEBUG
			checkOrganismStatus(organism, t, true); /* O(1) / O(OrgWC) + O(TC) */
#endif

			return t;
		}
	}

	/* O(OrgWC) */
	size_t DNACollector::organismCount() const
	{
		size_t count = 0;
		for (OrganismContainer::const_iterator it = m_organismContainer.begin(); it != m_organismContainer.end(); ++it)
			count += it->second.second.size();
		
		return count;
	}

	/* O(DnaC) */
	size_t DNACollector::dnaCount() const
	{
		size_t count = 0;

		for (DNAContainer::const_iterator containerIt = m_dnaContainer.begin(); containerIt != m_dnaContainer.end(); ++containerIt)
		{
			const DNAsByType& dnas = containerIt->second;
			for (DNAsByType::const_iterator dnasIt = dnas.begin(); dnasIt != dnas.end(); ++dnasIt)
			{
				const DNAList& typedDnas = dnasIt->second;
				count += typedDnas.size();
			}
		}

		return count;
	}

#ifdef POT_DEBUG
	/* O(1) / O(OrgWC) + O(TC) */
	void DNACollector::checkOrganismStatus(const BaseOrganism* ptr, const DNACollectorTimestamp& t, bool shouldBeAlive) const
	{
		OrganismContainer::const_iterator containerIt = m_organismContainer.find(ptr); /* O(1) / O(OrgWC) */
		ASSERT_RELEASE(containerIt != m_organismContainer.end());
		const OrganismByTimestamp& organisms = containerIt->second.second;
		OrganismByTimestamp::const_iterator organismIt = organisms.find(t); /* O(1) / O(TC) */
		ASSERT_DEBUG(organismIt != organisms.end());

		std::ostringstream oss;
		oss << "should be alive: " << Tools::bool2str(shouldBeAlive);
		ASSERT_DEBUG_MSG(organismIt->second.alive == shouldBeAlive, oss.str().c_str()); /* O(1) / O(TC) */
	}

	void DNACollector::checkIntegrityIFN()
	{
		m_checker.checkIntegrityIFN();
		return;
	}
#endif
}
