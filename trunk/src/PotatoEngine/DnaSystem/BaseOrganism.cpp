#include <stdafx.h>
#include "BaseOrganism.hpp"

#ifdef POT_DEBUG
# include <Debug/Callstack/AbstractCallstack.hpp>
#endif
#include <DnaSystem/DNA.hpp>
#include <DnaSystem/DNACollector.hpp>

namespace Pot
{
#ifdef POT_DEBUG
	const size_t BaseOrganism::c_framesToSkip = Debug::AbstractCallstack::c_defaultSkippedFrameCount;
#endif

	BaseOrganism::BaseOrganism()
#ifdef POT_DEBUG
		: m_callstack(c_framesToSkip, true)
#endif
	{}

	BaseOrganism::~BaseOrganism()
	{
		shutdown();
	}

	void BaseOrganism::shutdown() const
	{
		DNACollector::instance().notifyOrganismDeath(*this);
	}
}
