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
	BacktraceCallstack::BacktraceCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
		AbstractCallstack(skippedFrameCount, hasRealTimeConstraint),
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

	void BacktraceCallstack::setStackTrace(const std::string& trace)
	{
		m_trace = trace;
	}

	void BacktraceCallstack::fetchCallstack()
	{
		void* callstack[c_maxFrameCount];

		const size_t frameCount = static_cast<size_t>(backtrace(callstack, c_maxFrameCount));
		char** symbols = backtrace_symbols(callstack, frameCount);

		std::ostringstream oss;
		for (size_t i = m_skippedFrameCount; i < frameCount; ++i)
		{
			if (i > m_skippedFrameCount)
				oss << std::endl;

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
				    << " at " << getFileAndLine_internal(info.dli_saddr, lineBuffer)
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
						<< " at " << getFileAndLine_internal(symbols[i], lineBuffer);
				}
				else
					oss << symbols[i] << " at " << getFileAndLine_internal(symbols[i], lineBuffer);

				oss << " [dladdr failed for " << callstack[i] << "]";
			}
		}
		free(symbols);

		if (frameCount == c_maxFrameCount)
			oss << std::endl << "[possibly truncated]";

		m_trace = oss.str();
	}
}}

#endif
