#include <stdafx.h>
#include "BacktraceCallstack.hpp"

#ifdef POT_BACKTRACE_SUPPORT
#include <cstdio>
#include <cstring>
#include <dlfcn.h>
#include <execinfo.h>
#include <iomanip>
#include <sstream>

#include <Debug/Callstack/AbstractCallstack.hpp>
#include <Debug/assert.hpp>
#include <Debug/Demangler.hpp>

#include <fstream>

namespace Pot { namespace Debug
{
	BacktraceCallstack::BacktraceCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
		AbstractCallstack(skippedFrameCount, hasRealTimeConstraint),
		m_frameCount(0),
		m_adresses(nullptr),
		m_symbols(nullptr),
		m_currentInfo(),
		m_currentFrame(0),
		m_dlAddrSuccess(false)
	{
		init();
		fetchCallstack();
		cleanUp();
	}

	BacktraceCallstack::~BacktraceCallstack()
	{}

	void BacktraceCallstack::init()
	{
		AbstractCallstack::init();

		m_adresses = new void*[c_maxFrameCount];
		m_frameCount = static_cast<size_t>(backtrace(m_adresses, c_maxFrameCount));
		m_symbols = backtrace_symbols(m_adresses, m_frameCount);
	}

	void BacktraceCallstack::cleanUp()
	{
		AbstractCallstack::cleanUp();

		delete[] m_adresses;
		free(m_symbols);
	}

	void* BacktraceCallstack::fetchNextEntry(const size_t index)
	{
		m_currentFrame = index;
		m_dlAddrSuccess = false;

		if (index >= m_frameCount)
			return nullptr;

		if (dladdr(m_adresses[m_currentFrame], &m_currentInfo) != 0 && m_currentInfo.dli_sname != nullptr && m_currentInfo.dli_saddr != nullptr)
		{
			m_dlAddrSuccess = true;
			return m_currentInfo.dli_saddr;
		}

		return m_adresses[m_currentFrame];
	}

	bool BacktraceCallstack::fetchSymbolName(const void* const address, std::string& outSymbolName) const
	{
		POT_UNUSED(address);

		if (m_dlAddrSuccess)
		{
			ASSERT_DEBUG(m_currentInfo.dli_sname != nullptr);
			outSymbolName = Demangler(m_currentInfo.dli_sname, true).str();
		}
		else
		{
			// We skip the index to manually write it if possible
			const char* symbolStart = strchr(m_symbols[m_currentFrame], ' ');
			if (symbolStart != nullptr)
			{
				// Skip spaces
				while (*symbolStart == ' ')
					symbolStart++;
				outSymbolName = symbolStart;
			}
			else
				symbolStart = m_symbols[m_currentFrame];

			outSymbolName = symbolStart; // Demangle it ?
		}

		return true;
	}

	bool BacktraceCallstack::fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const
	{
#ifdef POT_PLATFORM_OSX
		if (realTimeConstraint)
			return false;
#endif

		const size_t bufferSize = 512;
		char command[bufferSize];

		ASSERT_DEBUG(c_programName != nullptr);
		if (c_programName == nullptr)
			return false;

		// Get file name and line from the address
#ifdef POT_PLATFORM_OSX
		snprintf(command, bufferSize, "xcrun atos -o %s %p", c_programName, address);
#elif defined(POT_COMPILER_MSC) && (_MSC_VER < 1900) // snprintf not implemented on MSC before VS 2015 ...
		sprintf(command, "addr2line -f -p -e %.256s %p", c_programName, address);
#else
		snprintf(command, bufferSize, "addr2line -f -p -e %.256s %p", c_programName, address);
#endif
		char buffer[bufferSize];
		const size_t maxReadBytes = bufferSize - 1;

#ifdef POT_PLATFORM_WINDOWS
		FILE* fpipe = _popen(command, "r");
#else
		FILE* fpipe = popen(command, "r");
#endif
		if (fpipe == nullptr)
		{
			Logger::log(Logger::CWarning, "AbstractCallstack::getLine: couldn't open pipe with command '%s'", command);
			return false;
		}

		const size_t readBytes = fread(buffer, sizeof(char), maxReadBytes, fpipe);

		/* Close pipe */
#ifdef POT_PLATFORM_WINDOWS
		_pclose(fpipe);
#else
		pclose(fpipe);
#endif

		ASSERT_RELEASE(readBytes <= maxReadBytes);
		// Add terminating '\0'
		buffer[readBytes] = '\0';
		// Get rid of an eventual terminating '\n'
		if (readBytes > 0 && buffer[readBytes - 1] == '\n')
			buffer[readBytes - 1] = '\0';

		// Parse command output to get [filename]:[line]
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

		outFileName = fileName;
		outLine = line:
#else
		ASSERT_NOT_IMPLEMENTED();
		return false;
#endif

		return true;
	}

	bool BacktraceCallstack::fetchBinaryName(const void* const address, std::string& outBinaryName) const
	{
		POT_UNUSED(address);

		if (!m_dlAddrSuccess)
			return false;

		// Fetch the binary containing the symbol (dli_fname stores the full path)
		const char* binaryName = m_currentInfo.dli_fname;
		if (binaryName != nullptr)
		{
			const char* lastSlash = strrchr(binaryName, '/');
			if (lastSlash != nullptr)
				binaryName = lastSlash + 1;
		}

		outBinaryName = binaryName;
		return true;
	}
}}

#endif
