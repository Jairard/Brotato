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

	const char* BacktraceCallstack::c_str() const
	{
		return m_trace.c_str();
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
				    << " at " << getFileAndLine(info.dli_saddr, lineBuffer)
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
					    << " at " << getFileAndLine(symbols[i], lineBuffer);
				}
				else
					oss << symbols[i] << " at " << getFileAndLine(symbols[i], lineBuffer);

				oss << " [dladdr failed for " << callstack[i] << "]";
			}

			oss << std::endl;
		}
		free(symbols);

		if (frameCount == c_maxFrameCount)
			oss << "[possibly truncated]" << std::endl;

		m_trace.assign(oss.str());
	}

	std::string& BacktraceCallstack::getFileAndLine(const void* const address, std::string& outString)
	{
		const size_t bufferSize = 512;
		char command[bufferSize];

		// Get file name and line from the adress
#ifdef POT_PLATFORM_OSX
		snprintf(command, bufferSize, "xcrun atos -o %s %p", c_programName, address); 
#else
		snprintf(command, bufferSize, "addr2line -f -p -e %.256s %p", c_programName, address); 
#endif

		char buffer[bufferSize];
		const size_t maxReadBytes = bufferSize - 1;

		FILE* fpipe = popen(command, "r");
		if (fpipe == nullptr)
		{
			Logger::log(Logger::CWarning, "BacktraceCallstack::getLine: couldn't open pipe with command '%s'", command);
			return outString;
		}

		const size_t readBytes = fread(buffer, sizeof(char), maxReadBytes, fpipe);
		pclose(fpipe);
		
		ASSERT_RELEASE(readBytes <= maxReadBytes);
		// Add terminating '\0'
		buffer[readBytes] = '\0';
		// Get rid of an eventual terminating '\n'
		if (readBytes > 0 && buffer[readBytes - 1] == '\n')
			buffer[readBytes - 1] = '\0';
		formatFileAndLine(buffer);

		// Output result to string
		ASSERT_DEBUG(outString.empty());
		outString.assign(buffer);
		if (readBytes == maxReadBytes)
			outString += " [possibly truncated]";

		return outString;
	}

	void BacktraceCallstack::formatFileAndLine(char buffer[])
	{
#ifdef POT_PLATFORM_OSX
		// Buffer contains something like "main (in PotatoEngine) (_potatoEngine_main.cpp:257)"
		const size_t maxFilenameSize = 128;
		char filename[maxFilenameSize];
		int line;

		// Look for last occurence of '('
		char* filenameStart = strrchr(buffer, '(');
		if (filenameStart == nullptr)
			return;
		filenameStart++;

		// Look for the occurence of ':' (from the end, it should be faster)
		char* semicolon = strrchr(buffer, ':');
		if (semicolon == nullptr)
			return;

		// Get filename
		const size_t filenameSize = semicolon - filenameStart;
		if (sscanf(filenameStart, "%s", filename) != 1)
			return;
		// At this point, filename = "_potatoEngine_main.cpp:257)", so we adjust it using the ':' position
		filename[filenameSize] = '\0';

		// Get line
		if (sscanf(semicolon + 1, "%d", &line) != 1)
			return;

		// No need to call snprintf because the size we print is strictly inferior to the input size
		sprintf(buffer, "%s:%d", filename, line);
#endif
	}
}}

#endif
