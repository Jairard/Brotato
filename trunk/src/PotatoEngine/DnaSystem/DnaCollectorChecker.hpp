#ifndef __POT_DNA_COLLECTOR_CHECKER__
#define __POT_DNA_COLLECTOR_CHECKER__

#include "../Core/compil.hpp"
#ifdef POT_DEBUG
#include "../Core/NonCopyable.hpp"
#include "../Core/types.hpp"

namespace Pot
{
	class DNACollector;
	class DNACollectorTimestamp;

	namespace Check
	{
		enum Type
		{
			Dna_TimestampValidity,              /* O(DnaWC) * O(OrgWC) / O(DnaWC) * O(OrgC) */
			Dna_NoEmptyList,                    /* O(DnaWC) */
			Dna_Uniqueness,                     /* O(DnaC * log(DnaC)) */
			Organism_TimestampUniqueness,       /* O(OrgC * log(OrgC)) */
			Organism_TimestampValidity,         /* O(OrgWC) / O(OrgWC) * O(DnaWC) */
			Organism_AliveTimestampIntegrity,   /* O(OrgWC) / O(OrgC) */
			Organism_TimestampStatusIntegrity,  /* O(OrgWC) * O(DnaC) */
			Length
		};
	}

	class DNACollectorChecker: public NonCopyable
	{
		public:
			DNACollectorChecker(const DNACollector& collector);
			void checkIntegrityIFN();
			void setFullCheckMode(bool fullCheck);

		private:
			Check::Type getCheckToPerform();

			void checkDnas_TimestampValidity() const;
			void checkDnas_NoEmptyList() const;
			void checkDnas_Uniqueness() const;
			void checkOrganisms_TimestampUniqueness() const;
			void checkOrganisms_TimestampValidity() const;
			void checkOrganisms_AliveTimestampIntegrity() const;
			void checkOrganisms_TimestampStatusIntegrity() const;

			bool checkDNAsStatus(const DNACollectorTimestamp& t, bool shouldBeAlive) const;
			void handleError(bool test, const char* msg) const;

		private:
			static const potu8 c_operationCountBetweenChecks;
			const DNACollector& m_collector;
			potu64 m_operationCount;
			Check::Type m_nextCheck;
			bool m_fullCheckMode;
	};
}
#endif

#endif
