#include "stdafx.h"
#include "BaseOrganism.hpp"

#include "DNA.hpp"
#include "DNACollector.hpp"

namespace Pot
{
	BaseOrganism::BaseOrganism()
	{}

	BaseOrganism::~BaseOrganism()
	{
		DNACollector::instance().notifyOrganismDeath(*this);
	}
}
