#include "BaseDNA.hpp"

#include "Debug/Logger.hpp"
#include "DNACollector.hpp"

namespace Pot
{
	using Debug::Logger;

	BaseDNA::BaseDNA():
		m_organism(nullptr)
	{
	}

	BaseDNA::~BaseDNA()
	{
	}

	const BaseOrganism* BaseDNA::organism() const
	{
		return m_organism;
	}

	void BaseDNA::selfRegister(const std::type_info& organismType)
	{
		DNACollector::instance().registerDNA(*this, organismType);
	}

	void BaseDNA::selfUnregister()
	{
		DNACollector::instance().unregisterDNA(*this);
	}

	void BaseDNA::onOrganismDeath(const BaseOrganism* organism)
	{
		ASSERT_DEBUG(organism == m_organism);
		Logger::log(Logger::CWarning, "%u.onOrganismDeath(%u)", this, organism);
		m_organism = nullptr;
	}
}
