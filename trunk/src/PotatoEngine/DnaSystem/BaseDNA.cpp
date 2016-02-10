#include <stdafx.h>
#include "BaseDNA.hpp"

#include <Debug/Logger.hpp>
#include <Dnasystem/DNACollector.hpp>

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

	bool BaseDNA::isValid() const
	{
		return m_organism != nullptr;
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
		POT_UNUSED(organism);
		ASSERT_DEBUG(organism == m_organism);
		m_organism = nullptr;
	}
}
