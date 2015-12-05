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

// TODO:
// - checkIntegrity
// - callstack
// - abstract timestamp handling
// - file .tpl
// - pool for [Organism|DNA]Info ?
// - check integrity ptr <-> type_info ?

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
	class BaseDNA;
	class BaseOrganism;

	namespace Debug
	{
		class Logger;
	}

	using Debug::Logger;

	class DNACollector: public Singleton<DNACollector>, public NonCopyable
	{
		template <typename T>
		friend class Singleton;
		friend class BaseDNA;
		friend class BaseOrganism;

		typedef potu64 Timestamp;

		struct DNAInfo
		{
			BaseDNA& dna;
			const BaseOrganism* organism;
#ifdef POT_DEBUG
			const char* callstack;
#endif

			DNAInfo(BaseDNA& _dna);
			DNAInfo& operator=(const DNAInfo& other);
		};

		struct OrganismInfo
		{
			const BaseOrganism* ptr;
#ifdef POT_DEBUG
			bool alive;
			const std::type_info& type;
			const char* callstack;
#endif

			OrganismInfo();
			OrganismInfo(const BaseOrganism* _ptr, const std::type_info& _type, bool _alive = true);
		};

		// DNA container
		typedef std::vector<DNAInfo> DNAList;
		typedef std::unordered_map<std::type_index, DNAList> DNAsByType;
		typedef std::unordered_map<Timestamp, DNAsByType> DNAContainer;

		// Organism container
		typedef std::unordered_map<Timestamp, OrganismInfo> OrganismByTimestamp;
		typedef std::pair<Timestamp, OrganismByTimestamp> OrganismsInfoForPointer; // Timestamp: aliveTimestamp
		typedef std::unordered_map<const BaseOrganism*, OrganismsInfoForPointer> OrganismContainer;

	protected:
		DNACollector();
		~DNACollector();

	public:
		static void dump(const char* tag);
		size_t memorySize() const;

	private:
		/* Release:                O(1) / O(OrgWC) + O(DnaWC) */
		/* Debug:   O(OrgWC) + O(DnaWC) / O(OrgC)  + O(DnaWC) */
		void registerDNA(BaseDNA& dna, const std::type_info& organismType);
		/* O(DnaTC) / O(DnaC) + O(OrgWC) | O(DnaC) * O(OrgC) */
		void unregisterDNA(BaseDNA& dna);
		/* O(DnaCTC) / O(OrgC) + O(DnaCTC) */
		void notifyOrganismDeath(const BaseOrganism& organism);

		void dump_internal(const char* tag) const;

		/* O(OrgC) */
		const OrganismInfo* getOrganismInfoFromTimestamp(const Timestamp& t) const;
		/* O(1) / O(OrgWC) | O(OrgC) */
		const Timestamp& createOrganismEntry(const BaseOrganism* ptr, const std::type_info& type);
		/* O(1) / O(OrgWC) | O(OrgC) */
		void clearOrganismInfoForTimestamp(const BaseOrganism* ptr, const Timestamp& t);
		/* Alive: O(1) / O(OrgWC) | O(OrgC) */
		/* Dead:  O(DnaC) | O(DnaC) * O(OrgC) */
		Timestamp fetchTimestamp(const BaseDNA& dna, const std::type_index& dnaTypeIndex, const BaseOrganism** outOrganism);
		/* O(OrgWC) */
		size_t organismCount() const;
		/* O(DnaC) */
		size_t dnaCount() const;

#ifdef POT_DEBUG
		/* O(1) / O(OrgC) */
		void checkOrganismStatus(const BaseOrganism* ptr, const Timestamp& t, bool shouldBeAlive); // Debug only
#endif

		private:
			static const Timestamp c_invalidTimestamp = std::numeric_limits<Timestamp>::max();
			DNAContainer m_dnaContainer;
			OrganismContainer m_organismContainer;
			Timestamp m_timestamp;
	};
}

#endif
