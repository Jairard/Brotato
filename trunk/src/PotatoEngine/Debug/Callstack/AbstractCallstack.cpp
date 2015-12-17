#include "../../stdafx.h"
#include "AbstractCallstack.hpp"

#include <sstream>
#include "../assert.hpp"
#include "../Logger.hpp"

namespace Pot { namespace Debug
{
	const size_t AbstractCallstack::c_defaultSkippedFrameCount = 3; // Maybe it'll be needed to specialize this constant
	const char* AbstractCallstack::c_programName = nullptr;
	const size_t AbstractCallstack::c_maxFrameCount = 128;

	AbstractCallstack::AbstractCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
		m_skippedFrameCount(skippedFrameCount),
		m_hasRealTimeConstraint(hasRealTimeConstraint)
	{}

	AbstractCallstack::~AbstractCallstack()
	{}

	void AbstractCallstack::operator=(const AbstractCallstack& other)
	{
		m_skippedFrameCount = other.m_skippedFrameCount;
		m_hasRealTimeConstraint = other.m_hasRealTimeConstraint;
		setStackTrace(other.str());
	}

	const char* AbstractCallstack::operator()() const
	{
		return c_str();
	}

	const char* AbstractCallstack::c_str() const
	{
		return str().c_str();
	}

	void AbstractCallstack::setProgramName(const char* name)
	{
		ASSERT_DEBUG(name != nullptr);

		if (c_programName != nullptr)
		{
			std::ostringstream oss;
			oss << "AbstractCallstack: trying to set program name twice !"
			    << " (" << c_programName << " -> " << name << ")";
			ASSERT_DEBUG_MSG(c_programName == nullptr, oss.str().c_str());
			return;
		}

		c_programName = name;
	}

	std::string& AbstractCallstack::getFileAndLine_internal(const void* address, std::string& outString) const
	{
		return outputFileAndLineFromAddress(address, outString, m_hasRealTimeConstraint);
	}

	std::string& AbstractCallstack::outputFileAndLineFromAddress(const void* const address, std::string& outString, bool realTimeConstraint)
	{
#ifdef POT_PLATFORM_OSX
		if (realTimeConstraint)
		{
			outString = "[location not available]";
			return outString;
		}
#endif

		const size_t bufferSize = 512;
		char command[bufferSize];

		ASSERT_DEBUG(c_programName != nullptr);
		if (c_programName == nullptr)
			return outString;

		// Get file name and line from the adress
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
			return outString;
		}

		const size_t readBytes = fread(buffer, sizeof(char), maxReadBytes, fpipe);

		/* Close pipe and print return value of pPipe. */
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
		formatFileAndLine(buffer);

		// Output result to string
		ASSERT_DEBUG(outString.empty());
		outString = buffer;
		if (readBytes == maxReadBytes)
			outString += " [possibly truncated]";

		return outString;
	}

	void AbstractCallstack::formatFileAndLine(char buffer[])
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

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::AbstractCallstack& callstack)
{
	stream << callstack.str();
	return stream;
}
