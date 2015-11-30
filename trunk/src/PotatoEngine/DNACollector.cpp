#include "DNACollector.hpp"

#include <sstream>

namespace Pot
{
	DNACollector::DNAInfo::DNAInfo():
		  ptr(nullptr)
		, organism(nullptr)
		, organismPtr(nullptr)
#ifdef POT_DEBUG
		, callstack(nullptr)
#endif
	{}

	// DNACollector::OrganismInfo
	DNACollector::OrganismInfo::OrganismInfo():
		  ptr(nullptr)
#ifdef POT_DEBUG
		, alive(false)
		, type(typeid(void))
		, callstack(nullptr)
#endif
	{}

	DNACollector::OrganismInfo::OrganismInfo(const void* _ptr, const std::type_info& _type, bool _alive):
		  ptr(_ptr)
#ifdef POT_DEBUG
		, alive(_alive)
		, type(_type)
		, callstack(nullptr)
#endif
	{
#ifndef POT_DEBUG
		UNUSED(_type);
		UNUSED(_alive);
#endif
	}

	// DNACollector
	DNACollector::DNACollector():
		m_dnaContainer(),
		m_organismContainer(),
		m_timestamp(0)
	{}

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

		Logger::log(tag, "Current timestamp: %llu", m_timestamp);
		Logger::log(tag, "Organism count: %u", organismCount());
		Logger::log(tag, "Dna count: %U", dnaCount());

		if (!m_organismContainer.empty())
			Logger::log(tag, "");

		for (OrganismContainer::const_iterator ptrIt = m_organismContainer.begin(); ptrIt != m_organismContainer.end(); ++ptrIt)
		{
			const void* ptr = ptrIt->first;
			const OrganismsInfoForPointer& infoForPtr = ptrIt->second;
			const Timestamp& aliveTimestamp = infoForPtr.first;
			const OrganismByTimestamp& organismsByTimestamp = infoForPtr.second;

			Logger::log(tag, "* Addess: %u (%u timestamps)", ptr, organismsByTimestamp.size());
			if (aliveTimestamp != INVALID_TIMESTAMP)
				Logger::log(tag, "  Is alive with timestamp %llu", aliveTimestamp);
			else
				Logger::log(tag, "  Is not alive");

			size_t i = 0;
			for (OrganismByTimestamp::const_iterator organismIt = organismsByTimestamp.begin(); organismIt != organismsByTimestamp.end(); ++organismIt)
			{
				const Timestamp& t = organismIt->first;

				Logger::log(tag, "[%u] Timestamp: %llu", i, t);
#ifdef POT_DEBUG
				const OrganismInfo& info = organismIt->second;
				Logger::log(tag, "      Alive: %s", Tools::bool2str(info.alive));
				Logger::log(tag, "      Type: %s", info.type.name());
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

			Logger::log(tag, "DNAs registered for organism %u:%llu (in %d type(s)):", organismInfo.ptr, containerIt->first, dnas.size());
			for (DNAsByType::const_iterator dnasIt = dnas.begin(); dnasIt != dnas.end(); ++dnasIt)
			{
				const std::type_index& type = dnasIt->first;
				const DNAList& typedDnas = dnasIt->second;

				Logger::log(tag, "* %s (%u element(s))", type.name(), typedDnas.size());
				for (size_t i = 0; i < typedDnas.size(); ++i)
				{
					const DNAInfo& dnaInfo = typedDnas[i];
					Logger::log(tag, "[%u] ptr: %u:", i, dnaInfo.ptr);
					Logger::log(tag, "     organimsPtr: %u", dnaInfo.organismPtr);
					Logger::log(tag, "     organism: %u", *dnaInfo.organismPtr);
					Logger::log(tag, "     timestamp: %llu", containerIt->first);
				}
			}
		}

		Logger::log(tag, "===================================");
	}

	/* O(OrgC) */
	const DNACollector::OrganismInfo* DNACollector::getOrganismInfoFromTimestamp(const Timestamp& t) const
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
	const DNACollector::Timestamp& DNACollector::createOrganismEntry(const void* ptr, const std::type_info& type)
	{
		const Timestamp& t = m_timestamp++;

		OrganismsInfoForPointer& infoForPtr = m_organismContainer[ptr]; /* O(1) / O(OrgWC) */
		const bool isAlive = (ptr != nullptr);
		OrganismInfo organismInfo(ptr, type, isAlive);
		infoForPtr.second.insert(std::make_pair(t, organismInfo));

		Timestamp& aliveTimestamp = infoForPtr.first;
		aliveTimestamp = t;

#ifdef POT_DEBUG
		OrganismByTimestamp& organisms = infoForPtr.second;
		ASSERT_DEBUG(organisms.find(t) != organisms.end()); /* O(1) / O(TC) */
		ASSERT_DEBUG(organisms[t].alive == isAlive); /* O(1) / O(TC) */
#endif

		return	aliveTimestamp;
	}
	
	/* O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
	void DNACollector::clearOrganismInfoForTimestamp(const void* ptr, const Timestamp& t)
	{
		Logger::log(Logger::CWarning, "clearOrganismInfoForTimestamp: ptr(%u), t(%llu)", ptr, t);
		ASSERT_DEBUG(m_organismContainer.find(ptr) != m_organismContainer.end()); /* O(1) / O(OrgWC) */
		OrganismsInfoForPointer& infoForPtr = m_organismContainer[ptr]; /* O(1) / O(OrgWC) */

		OrganismByTimestamp& timestamps = infoForPtr.second;
		// Clearing a timestamp that is not registered
		ASSERT_DEBUG(timestamps.find(t) != timestamps.end()); /* O(1) / O(TC) */

		Timestamp& aliveTimestamp = infoForPtr.first;
		if (aliveTimestamp == t)
			aliveTimestamp = INVALID_TIMESTAMP;
		
		timestamps.erase(t);
		if (timestamps.empty())
			m_organismContainer.erase(ptr); /* O(1) / O(OrgWC) */
		
		dump(Logger::CWarning);
	}

	/* Alive: O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
	/* Dead:  O(DnaC) | O(DnaC) * (O(OrgWC) + O(TC)) */
	DNACollector::Timestamp DNACollector::fetchTimestamp(const void* dnaPtr, const std::type_index& dnaTypeIndex, const void* organismPtr, const void** outOrganismPtr)
	{
		ASSERT_DEBUG(dnaPtr != nullptr);
		if (organismPtr == nullptr) // Organism is dead, we have to fetch the organism ptr in the DNA container
		{
			/* O(DnaC) | O(DnaC) * (O(OrgWC) + O(TC)) */
			for (DNAContainer::const_iterator containerIt = m_dnaContainer.begin(); containerIt != m_dnaContainer.end(); ++containerIt)
			{
				const Timestamp& t = containerIt->first;
				const DNAsByType& dnas = containerIt->second;
				DNAsByType::const_iterator dnaIt = dnas.find(dnaTypeIndex);
				if (dnaIt == dnas.end())
					continue;

				const DNAList typedDnas = dnaIt->second;
				for (DNAList::const_iterator it = typedDnas.begin(); it != typedDnas.end(); ++it)
				{
					if (it->ptr == dnaPtr)
					{
						if (outOrganismPtr != nullptr)
							*outOrganismPtr = it->organism;
						ASSERT_DEBUG(t != INVALID_TIMESTAMP);
#ifdef POT_DEBUG
						checkOrganismStatus(*outOrganismPtr, t, false); /* O(1) / O(OrgWC) + O(TC) */
#endif
						return t;
					}
				}
			}

			ASSERT_NOT_REACHED();
			return INVALID_TIMESTAMP;
		}
		else // Organism is alive, we can directly look in the organism container
		{
			/* O(1) / O(OrgWC) | O(OrgWC) + O(TC) */
			ASSERT_DEBUG(m_organismContainer.find(organismPtr) != m_organismContainer.end()); /* O(1) / O(OrgWC) */
			const OrganismsInfoForPointer& infoForPtr = m_organismContainer[organismPtr]; /* O(1) / O(OrgWC) */
			const Timestamp& t = infoForPtr.first;
			ASSERT_RELEASE(t != INVALID_TIMESTAMP);

#ifdef POT_DEBUG
			checkOrganismStatus(organismPtr, t, true); /* O(1) / O(OrgWC) + O(TC) */
#endif

			return t;
		}
	}

#ifdef POT_DEBUG
	/* O(1) / O(OrgWC) + O(TC) */
	void DNACollector::checkOrganismStatus(const void* ptr, const Timestamp& t, bool shouldBeAlive)
	{
		OrganismByTimestamp& organisms = m_organismContainer[ptr].second; /* O(1) / O(OrgWC) */
		ASSERT_DEBUG(organisms.find(t) != organisms.end()); /* O(1) / O(TC) */

		std::ostringstream oss;
		oss << "should be alive: " << Tools::bool2str(shouldBeAlive);
		ASSERT_DEBUG_MSG(organisms[t].alive == shouldBeAlive, oss.str().c_str()); /* O(1) / O(TC) */
	}
#endif

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
}
