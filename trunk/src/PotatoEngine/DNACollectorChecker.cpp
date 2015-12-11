#include "DnaCollectorChecker.hpp"

#ifdef POT_DEBUG
#include <set>
#include "Debug/Logger.hpp"
#include "Debug/Demangler.hpp"
#include "DNACollector.hpp"
#include "DNACollectorTimestamp.hpp"
#include "BaseDNA.hpp"

namespace Pot
{
	using Debug::Logger;
	using Debug::Demangler;

	const potu8 DNACollectorChecker::c_operationCountBetweenChecks = 1;

	DNACollectorChecker::DNACollectorChecker(const DNACollector& collector):
		m_collector(collector),
		m_operationCount(0),
		m_nextCheck(Check::Dna_TimestampValidity),
		m_fullCheckMode(false)
	{}

	void DNACollectorChecker::checkIntegrityIFN()
	{
		if (!m_fullCheckMode)
		{
			Check::Type check = getCheckToPerform();

			switch (check)
			{
				// 1. DNA container properties
				case Check::Dna_TimestampValidity:
					// 1.1 Every timestamp corresponds to a referenced organism
					checkDnas_TimestampValidity();
					break;
				case Check::Dna_NoEmptyList:
					// 1.2 There is no empty list (except the container itself)
					checkDnas_NoEmptyList();
					break;
				case Check::Dna_Uniqueness:
					// 1.3 A DNA is stored once
					checkDnas_Uniqueness();
					break;

				// 2. Organism container properties
				case Check::Organism_TimestampUniqueness:
					// 2.1 A timestamp can only be used by one type
					checkOrganisms_TimestampUniqueness();
					break;
				case Check::Organism_TimestampValidity:
					// 2.2 A timestamp referenced in the organism container is also referenced in the DNA container
					checkOrganisms_TimestampValidity();
					break;
				case Check::Organism_AliveTimestampIntegrity:
					// 2.3 If an organism is alive, its 'aliveTimestamp' is valid
					checkOrganisms_AliveTimestampIntegrity();
					break;
				case Check::Organism_TimestampStatusIntegrity:
					// 2.4 If an organism is alive (dead), all its DNAs should have a valid(null) pointer
					checkOrganisms_TimestampStatusIntegrity();
					break;

				case Check::Length:
					return;
				default:
					ASSERT_NOT_REACHED();
					return;
			}
		}
		else
		{
			checkDnas_TimestampValidity();
			checkDnas_NoEmptyList();
			checkDnas_Uniqueness();
			checkOrganisms_TimestampUniqueness();
			checkOrganisms_TimestampValidity();
			checkOrganisms_AliveTimestampIntegrity();
		}
	}

	void DNACollectorChecker::setFullCheckMode(bool fullCheck)
	{
		m_fullCheckMode = fullCheck;
	}

	Check::Type DNACollectorChecker::getCheckToPerform()
	{
		Check::Type currentCheck = Check::Length;
		// We don't care about overflow on 'operationCount', even though it may disturb the check frequency a little bit
		if (++m_operationCount % c_operationCountBetweenChecks == 0)
		{
			currentCheck = m_nextCheck;
			m_nextCheck = static_cast<Check::Type>((m_nextCheck + 1) % Check::Length);
		}

		return currentCheck;
	}

	/* O(DnaWC) * O(OrgWC) / O(DnaWC) * O(OrgC) */
	void DNACollectorChecker::checkDnas_TimestampValidity() const
	{
		const DNACollector::DNAContainer& dnaContainer = m_collector.m_dnaContainer;
		const DNACollector::OrganismContainer& organismContainer = m_collector.m_organismContainer;
		DNACollector::DNAContainer::const_iterator containerIt;

		for (containerIt = dnaContainer.begin(); containerIt != dnaContainer.end(); ++containerIt)
		{
			const DNACollectorTimestamp& t = containerIt->first;

			/* O(OrgWC) / O(OrgC) */
			DNACollector::OrganismContainer::const_iterator orgContainerIt;
			for (orgContainerIt = organismContainer.begin(); orgContainerIt != organismContainer.end(); ++orgContainerIt)
			{
				const DNACollector::OrganismByTimestamp& organisms = orgContainerIt->second.second;
				if (organisms.find(t) != organisms.end()) /* O(1) / O(TC) */
					break;
			}

			std::ostringstream oss;
			oss << "DNACollector::checkIntegrity: ";
			oss << "some DNAs use timestamp " << t << " but no referenced organism have it";
			handleError(orgContainerIt != m_collector.m_organismContainer.end(), oss.str().c_str());
		}
	}

	/* O(DnaWC) */
	void DNACollectorChecker::checkDnas_NoEmptyList() const
	{
		const DNACollector::DNAContainer& dnaContainer = m_collector.m_dnaContainer;
		DNACollector::DNAContainer::const_iterator containerIt;

		for (containerIt = dnaContainer.begin(); containerIt != dnaContainer.end(); ++containerIt)
		{
			const DNACollectorTimestamp& t = containerIt->first;
			const DNACollector::DNAsByType& dnas = containerIt->second;

			std::ostringstream oss;
			oss << "DNACollector::checkIntegrity: ";
			oss << "the DNAsByType is empty for timestamp " << t;
			handleError(!dnas.empty(), oss.str().c_str());

			DNACollector::DNAsByType::const_iterator dnaIt;
			for (dnaIt = dnas.begin(); dnaIt != dnas.end(); ++dnaIt)
			{
				const DNACollector::DNAList& typedDnas = dnaIt->second;

				std::ostringstream oss;
				oss << "DNACollector::checkIntegrity: ";
				oss << "the DNAList is empty for timestamp " << t << " and type " << Demangler(dnaIt->first);
				handleError(!typedDnas.empty(), oss.str().c_str());
			}
		}
	}

	/* O(DnaC * log(DnaC)) */
	void DNACollectorChecker::checkDnas_Uniqueness() const
	{
		const DNACollector::DNAContainer& dnaContainer = m_collector.m_dnaContainer;
		DNACollector::DNAContainer::const_iterator containerIt;
		std::set<const BaseDNA*> dnaBuffer;

		for (containerIt = dnaContainer.begin(); containerIt != dnaContainer.end(); ++containerIt)
		{
			const DNACollector::DNAsByType& dnas = containerIt->second;
			DNACollector::DNAsByType::const_iterator dnaIt;

			for (dnaIt = dnas.begin(); dnaIt != dnas.end(); ++dnaIt)
			{
				const DNACollector::DNAList& typedDnas = dnaIt->second;
				DNACollector::DNAList::const_iterator it;

				for (it = typedDnas.begin(); it != typedDnas.end(); ++it)
				{
					const BaseDNA* dnaPtr = &(it->dna);
					const std::pair<std::set<const BaseDNA*>::iterator, bool> res = dnaBuffer.insert(dnaPtr);
					const bool alreadyIn = !res.second;

					std::ostringstream oss;
					oss << "DNACollector::checkIntegrity: ";
					oss << "the DNA " << dnaPtr << " is stored more than once";
					handleError(!alreadyIn, oss.str().c_str());
				}
			}
		}
	}

	/* O(OrgC * log(OrgC)) */
	void DNACollectorChecker::checkOrganisms_TimestampUniqueness() const
	{
		const DNACollector::OrganismContainer& organismContainer = m_collector.m_organismContainer;
		DNACollector::OrganismContainer::const_iterator containerIt;
		std::set<DNACollectorTimestamp> timestampBuffer;

		for (containerIt = organismContainer.begin(); containerIt != organismContainer.end(); ++containerIt)
		{
			const DNACollector::OrganismByTimestamp& timestamps = containerIt->second.second;
			DNACollector::OrganismByTimestamp::const_iterator it;

			for (it = timestamps.begin(); it != timestamps.end(); ++it)
			{
				DNACollectorTimestamp t = it->first;
				std::pair<std::set<DNACollectorTimestamp>::iterator, bool> res = timestampBuffer.insert(t);
				const bool alreadyIn = !res.second;

				std::ostringstream oss;
				oss << "DNACollector::checkIntegrity: ";
				oss << "the timestamp " << t << " is used by several types";
				handleError(!alreadyIn, oss.str().c_str());
			}
		}
	}

	/* O(OrgWC) / O(OrgWC) * O(DnaWC) */
	void DNACollectorChecker::checkOrganisms_TimestampValidity() const
	{
		const DNACollector::DNAContainer& dnaContainer = m_collector.m_dnaContainer;
		const DNACollector::OrganismContainer& organismContainer = m_collector.m_organismContainer;
		DNACollector::OrganismContainer::const_iterator containerIt;

		for (containerIt = organismContainer.begin(); containerIt != organismContainer.end(); ++containerIt)
		{
			const DNACollector::OrganismByTimestamp& timestamps = containerIt->second.second;
			DNACollector::OrganismByTimestamp::const_iterator it;

			for (it = timestamps.begin(); it != timestamps.end(); ++it)
			{
				const DNACollectorTimestamp& t = it->first;

				std::ostringstream oss;
				oss << "DNACollector::checkIntegrity: ";
				oss << "the timestamp " << t << " is not used by DNAs but still referenced in organism container";
				handleError(dnaContainer.find(t) != dnaContainer.end(), oss.str().c_str()); /* O(1) / O(DnaWC) */
			}
		}
	}

	/* O(OrgWC) / O(OrgC) */
	void DNACollectorChecker::checkOrganisms_AliveTimestampIntegrity() const
	{
		const DNACollector::OrganismContainer& organismContainer = m_collector.m_organismContainer;
		DNACollector::OrganismContainer::const_iterator containerIt;

		for (containerIt = organismContainer.begin(); containerIt != organismContainer.end(); ++containerIt)
		{
			const DNACollectorTimestamp& aliveTimestamp = containerIt->second.first;
			if (aliveTimestamp == DNACollectorTimestamp::c_invalid)
				continue;

			const DNACollector::OrganismByTimestamp& timestamps = containerIt->second.second;

			std::ostringstream oss;
			oss << "DNACollector::checkIntegrity: ";
			oss << "the organism " << containerIt->first << " is tagged alive with timestamp " << aliveTimestamp;
			oss << " but it does not correspond to a know timestamp";
			handleError(timestamps.find(aliveTimestamp) != timestamps.end(), oss.str().c_str()); /* O(1) / O(OrgTC) */
		}
	}

	/* O(OrgWC) * O(DnaC) */
	void DNACollectorChecker::checkOrganisms_TimestampStatusIntegrity() const
	{
		const DNACollector::OrganismContainer& organismContainer = m_collector.m_organismContainer;
		DNACollector::OrganismContainer::const_iterator containerIt;

		for (containerIt = organismContainer.begin(); containerIt != organismContainer.end(); ++containerIt)
		{
			const DNACollector::OrganismByTimestamp& timestamps = containerIt->second.second;
			DNACollector::OrganismByTimestamp::const_iterator it;

			for (it = timestamps.begin(); it != timestamps.end(); ++it)
			{
				const DNACollectorTimestamp& t = it->first;
				const bool alive = it->second.alive;

				std::ostringstream oss;
				oss << "DNACollector::checkIntegrity: ";
				oss << "the organism " << (long)containerIt->first << " is " << (alive ? "alive" : "dead");
				oss << " but some DNAs referencing it are " << (alive ? "dead" : "alive");
				handleError(checkDNAsStatus(t, alive), oss.str().c_str()); /* O(DnaC) */
			}
		}
	}

	bool DNACollectorChecker::checkDNAsStatus(const DNACollectorTimestamp& t, bool shouldBeAlive) const
	{
		const DNACollector::DNAContainer& dnaContainer = m_collector.m_dnaContainer;
		DNACollector::DNAContainer::const_iterator containerIt = dnaContainer.find(t);
		ASSERT_RELEASE(containerIt != dnaContainer.end());

		const DNACollector::DNAsByType& dnas = containerIt->second;
		DNACollector::DNAsByType::const_iterator dnasIt;

		for (dnasIt = dnas.begin(); dnasIt != dnas.end(); ++dnasIt)
		{
			const DNACollector::DNAList& typedDNAs = dnasIt->second;
			DNACollector::DNAList::const_iterator typedIt;

			for (typedIt = typedDNAs.begin(); typedIt != typedDNAs.end(); ++typedIt)
			{
				bool isAlive = typedIt->dna.isValid();
				if (isAlive != shouldBeAlive)
					return false;
			}
		}

		return true;
	}

	void DNACollectorChecker::handleError(bool test, const char* msg) const
	{
		if (!test)
		{
			DNACollector::dump(Logger::CError);
			ASSERT_DEBUG_MSG(test, msg);
		}
	}
}
#endif
