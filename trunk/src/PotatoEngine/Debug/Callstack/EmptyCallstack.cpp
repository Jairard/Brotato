#include <stdafx.h>
#include "EmptyCallstack.hpp"

#include <Core/Tools.hpp>

namespace Pot { namespace Debug 
{
	EmptyCallstack::EmptyCallstack(size_t sizetDummy, bool boolDummy):
		AbstractCallstack(0, false)
	{
		POT_UNUSED(sizetDummy);
		POT_UNUSED(boolDummy);
	}

	EmptyCallstack::~EmptyCallstack()
	{}

	void* EmptyCallstack::fetchNextEntry(const size_t index)
	{
		POT_UNUSED(index);
		return nullptr;
	}

	bool EmptyCallstack::fetchSymbolName(const void* const address, std::string& outSymbolName) const
	{
		POT_UNUSED(address);
		POT_UNUSED(outSymbolName);

		return false;
	}

	bool EmptyCallstack::fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const
	{
		POT_UNUSED(address);
		POT_UNUSED(outFileName);
		POT_UNUSED(outLine);

		return false;
	}

	bool EmptyCallstack::fetchBinaryName(const void* const address, std::string& outBinaryName) const
	{
		POT_UNUSED(address);
		POT_UNUSED(outBinaryName);

		return false;
	}
}}
