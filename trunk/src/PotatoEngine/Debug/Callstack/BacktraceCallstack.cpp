#include "../../stdafx.h"
#include "BacktraceCallstack.hpp"

#ifdef POT_BACKTRACE_SUPPORT
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <execinfo.h>
#include <dlfcn.h>
#include "../assert.hpp"
#include "../Demangler.hpp"
#include "AbstractCallstack.hpp"

#include <fstream>

namespace Pot { namespace Debug
{
	BacktraceCallstack::BacktraceCallstack(size_t skippedFrameCount):
		AbstractCallstack(skippedFrameCount),
		m_trace()
	{
		fetchCallstack();
	}

	BacktraceCallstack::~BacktraceCallstack()
	{}

	const std::string& BacktraceCallstack::str() const
	{
		return m_trace;
	}

	void BacktraceCallstack::fetchCallstack()
	{
		void* callstack[c_maxFrameCount];

		const size_t frameCount = static_cast<size_t>(backtrace(callstack, c_maxFrameCount));
		char** symbols = backtrace_symbols(callstack, frameCount);

		std::ostringstream oss;
		for (size_t i = m_skippedFramesCount; i < frameCount; ++i)
		{
			std::string lineBuffer;

			Dl_info info;
			if (dladdr(callstack[i], &info) != 0 && info.dli_sname != nullptr && info.dli_saddr != nullptr)
			{
				// Fetch the binary containing the symbol (dli_fname stores the full path)
				const char* binaryName = info.dli_fname;
				if (binaryName != nullptr)
				{
					const char* lastSlash = strrchr(binaryName, '/');
					if (lastSlash != nullptr)
						binaryName = lastSlash + 1;
				}

				oss << "[" << std::setw(3) << std::right << i << "] "
					<< Demangler(info.dli_sname, true)
					<< " at " << outputFileAndLineFromAddress(info.dli_saddr, lineBuffer)
					<< " (in " << binaryName << ")";
			}
			else
			{
				// We skip the index to manually write it if possible
				const char* symbolStart = strchr(symbols[i], ' ');
				if (symbolStart != nullptr)
				{
					// Skip spaces
					while (*symbolStart == ' ')
						symbolStart++;

					oss << "[" << std::setw(3) << std::right << i << "] " << symbolStart
						<< " at " << outputFileAndLineFromAddress(symbols[i], lineBuffer);
				}
				else
					oss << symbols[i] << " at " << outputFileAndLineFromAddress(symbols[i], lineBuffer);

				oss << " [dladdr failed for " << callstack[i] << "]";
			}

			oss << std::endl;
		}
		free(symbols);

		if (frameCount == c_maxFrameCount)
			oss << "[possibly truncated]" << std::endl;

		m_trace.assign(oss.str());
	}
}}

#endif
