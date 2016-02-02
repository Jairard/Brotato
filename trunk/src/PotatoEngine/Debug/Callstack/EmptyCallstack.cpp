#include "../../stdafx.h"
#include "EmptyCallstack.hpp"

#include "../../Core/Tools.hpp"

namespace Pot { namespace Debug 
{
	const std::string EmptyCallstack::c_message = "[no callstack support]";
		
	EmptyCallstack::EmptyCallstack(size_t sizetDummy, bool boolDummy):
		AbstractCallstack(0, false)
	{
		POT_UNUSED(sizetDummy);
		POT_UNUSED(boolDummy);
	}

	EmptyCallstack::~EmptyCallstack()
	{}

	const std::string& EmptyCallstack::str() const
	{
		return c_message;
	}

	void EmptyCallstack::setStackTrace(const std::string& trace)
	{
		POT_UNUSED(trace);
	}
}}
