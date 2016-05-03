#ifndef __POT_DNA_COLLECTOR__
#define __POT_DNA_COLLECTOR__

#include <functional>
#include <limits>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>
#include <vector>

#include <Core/NonCopyable.hpp>
#include <Core/Singleton.hpp>
#include <Core/Tools.hpp>
#include <Core/types.hpp>
#include <Debug/assert.hpp>
#include <Debug/Callstack.hpp>
#include <DnaSystem/CollectorChecker.hpp>
#include <DnaSystem/CollectorTimestamp.hpp>

// TODO:
// - Look for complexity improvements

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

namespace Debug
{
	class Logger;
}

namespace DnaSystem
{
	class BaseDNA;
	class BaseOrganism;

	using Debug::Logger;
	using Debug::Callstack;

	class Collector: public Singleton<Collector>, public NonCopyable
	{
		template <typename T>
		friend class Singleton;
		friend class BaseDNA;
		friend class BaseOrganism;
#ifdef POT_DEBUG
		friend class CollectorChecker;
#endif

	private:
		struct DNAInfo
		{
			BaseDNA& dna;
			const BaseOrganism* organism;
#ifdef POT_DEBUG
			Callstack callstack;
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
			Callstack callstack;
#endif

			OrganismInfo();
			OrganismInfo(const BaseOrganism* _ptr, const std::type_info& _type, bool _alive = true);
		};

		// DNA container
		typedef std::vector<DNAInfo> DNAList;
		typedef std::unordered_map<std::type_index, DNAList> DNAsByType;
		typedef std::unordered_map<CollectorTimestamp, DNAsByType> DNAContainer;

		// Organism container
		typedef std::unordered_map<CollectorTimestamp, OrganismInfo> OrganismByTimestamp;
		typedef std::pair<CollectorTimestamp, OrganismByTimestamp> OrganismsInfoForPointer; // CollectorTimestamp: aliveTimestamp
		typedef std::unordered_map<const BaseOrganism*, OrganismsInfoForPointer> OrganismContainer;

	protected:
		Collector();
		~Collector();

	public:
		static void dump(const char* tag = c_tag);
		static const char* tag();
		static void setFullCheckMode(bool enabled);

		size_t memorySize() const;
		/* O(OrgWC) */
		size_t organismCount() const;
		/* O(DnaC) */
		size_t dnaCount() const;

	private:
		/* Release:                O(1) / O(OrgWC) + O(DnaWC) */
		/* Debug:   O(OrgWC) + O(DnaWC) / O(OrgC)  + O(DnaWC) */
		void registerDNA(BaseDNA& dna, const std::type_info& organismType);
		/* O(DnaTC) / O(DnaC) + O(OrgWC) | O(DnaC) * O(OrgC) */
		void unregisterDNA(BaseDNA& dna);
		/* O(DnaCTC) / O(OrgC) + O(DnaCTC) */
		void notifyOrganismDeath(const BaseOrganism& organism);

		void dump_internal(std::ostream& outStream, bool displayCallstacks) const;

		/* O(OrgC) */
		const OrganismInfo* getOrganismInfoFromTimestamp(const CollectorTimestamp& t) const;
		/* O(1) / O(OrgWC) | O(OrgC) */
		const CollectorTimestamp& createOrganismEntry(const BaseOrganism* ptr, const std::type_info& type);
		/* O(1) / O(OrgWC) | O(OrgC) */
		void clearOrganismInfoForTimestamp(const BaseOrganism* ptr, const CollectorTimestamp& t);
		/* Alive: O(1) / O(OrgWC) | O(OrgC) */
		/* Dead:  O(DnaC) | O(DnaC) * O(OrgC) */
		CollectorTimestamp fetchTimestamp(const BaseDNA& dna, const std::type_index& dnaTypeIndex, const BaseOrganism** outOrganism) const;

#ifdef POT_DEBUG
		/* O(1) / O(OrgC) */
		void checkOrganismStatus(const BaseOrganism* ptr, const CollectorTimestamp& t, bool shouldBeAlive) const;
		void checkIntegrityIFN();
#endif

		private:
			static const char* c_tag;
			static const size_t c_framesToSkipForDNAInfo;
			static const size_t c_framesToSkipForOrganismInfo;
			DNAContainer m_dnaContainer;
			OrganismContainer m_organismContainer;
			CollectorTimestamp m_timestamp;
#ifdef POT_DEBUG
			CollectorChecker m_checker;
#endif
	};
}}

#endif