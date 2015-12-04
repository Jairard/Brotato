#include "../../stdafx.h"
#include "EmptyCallstack.hpp"

#include "../../Core/Tools.hpp"

namespace Pot { namespace Debug 
{
	const std::string EmptyCallstack::c_message = "[no callstack support]";
		
	EmptyCallstack::EmptyCallstack(size_t skippedFrameCount):
		AbstractCallstack(0)
	{
		POT_UNUSED(skippedFrameCount);
	}

	EmptyCallstack::~EmptyCallstack()
	{}

	const std::string& EmptyCallstack::str() const
	{
		return c_message;
	}

	const char* EmptyCallstack::c_str() const
	{
		return c_message.c_str();
	}
}}
