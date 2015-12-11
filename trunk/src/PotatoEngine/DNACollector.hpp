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
#include "DnaCollectorChecker.hpp"
#include "DNACollectorTimestamp.hpp"

// TODO:
// - callstack
// - logs: type (remove "const*")
// - Look for complexity improvements
// - separate folder/namespace ?

/*
 * Complexity notations:
 * - OrgC: organism count. If a pointer has several timestamps, they are included.
 * - OrgWC: organisms weak count. If a pointer has several timestamps, it counts as 1.
 * - TC: timestamp count. Number of timestamps for the current organism.
 * - DnaC: dna count. If a timestamp as several dnas per type, each of them counts as 1.
 * - DnaWC: dna weak count. If a timestamp as several dnas per type, it counts as 1.
 * - DnaTC: dna type count. Number of different dna types for the current timestamp.
 * - DnaCTC: dna current timestamp count. Number of dnas for the current timestamp.
 * - O(v1) | O(v2) / O(v3) | O(v4): amortized complexity in release | debug / worst case complexity in release | debug.
 *
 * For readability's sake, approximations O(OrgWC) + O(TC) = O(OrgC) and O(DnaWC) + O(DnaTC) = O(DnaC) may be done.
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
#ifdef POT_DEBUG
		friend class DNACollectorChecker;
#endif

	private:
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
		typedef std::unordered_map<DNACollectorTimestamp, DNAsByType> DNAContainer;

		// Organism container
		typedef std::unordered_map<DNACollectorTimestamp, OrganismInfo> OrganismByTimestamp;
		typedef std::pair<DNACollectorTimestamp, OrganismByTimestamp> OrganismsInfoForPointer; // DNACollectorTimestamp: aliveTimestamp
		typedef std::unordered_map<const BaseOrganism*, OrganismsInfoForPointer> OrganismContainer;

	protected:
		DNACollector();
		~DNACollector();

	public:
		static void dump(const char* tag = c_tag);
		static const char* tag();
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
		const OrganismInfo* getOrganismInfoFromTimestamp(const DNACollectorTimestamp& t) const;
		/* O(1) / O(OrgWC) | O(OrgC) */
		const DNACollectorTimestamp& createOrganismEntry(const BaseOrganism* ptr, const std::type_info& type);
		/* O(1) / O(OrgWC) | O(OrgC) */
		void clearOrganismInfoForTimestamp(const BaseOrganism* ptr, const DNACollectorTimestamp& t);
		/* Alive: O(1) / O(OrgWC) | O(OrgC) */
		/* Dead:  O(DnaC) | O(DnaC) * O(OrgC) */
		DNACollectorTimestamp fetchTimestamp(const BaseDNA& dna, const std::type_index& dnaTypeIndex, const BaseOrganism** outOrganism) const;
		/* O(OrgWC) */
		size_t organismCount() const;
		/* O(DnaC) */
		size_t dnaCount() const;

#ifdef POT_DEBUG
		/* O(1) / O(OrgC) */
		void checkOrganismStatus(const BaseOrganism* ptr, const DNACollectorTimestamp& t, bool shouldBeAlive) const;
		void checkIntegrityIFN();
#endif

		private:
			static const char* c_tag;
			DNAContainer m_dnaContainer;
			OrganismContainer m_organismContainer;
			DNACollectorTimestamp m_timestamp;
#ifdef POT_DEBUG
			DNACollectorChecker m_checker;
#endif
	};
}

#endif
