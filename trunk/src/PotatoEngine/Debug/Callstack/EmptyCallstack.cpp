#include "../../stdafx.h"
#include "EmptyCallstack.hpp"

#include "../../Core/Tools.hpp"

namespace Pot { namespace Debug 
{
	const std::string EmptyCallstack::c_message = "[no callstack support]";
		
	EmptyCallstack::EmptyCallstack(size_t skippedFrameCount):
		AbstractCallstack(0, false)
	{
		POT_UNUSED(skippedFrameCount);
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
