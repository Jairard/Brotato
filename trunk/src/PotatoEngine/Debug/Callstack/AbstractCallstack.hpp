#ifndef __POT_DEBUG_ABSTRACT_CALLSTACK__
#define __POT_DEBUG_ABSTRACT_CALLSTACK__

#include <string>
#include <ostream>

namespace Pot { namespace Debug
{
class AbstractCallstack
{
	public:
		AbstractCallstack(size_t skippedFrameCount);
		virtual ~AbstractCallstack();

		const char* operator()() const;
		const char* c_str() const;
		virtual const std::string& str() const = 0;

		static void setProgramName(const char* name);
		static std::string& outputFileAndLineFromAddress(const void* const address, std::string& outString);

	private:
		static void formatFileAndLine(char buffer[]);

	public:
		static const char* c_programName;
		static const size_t c_maxFrameCount;
		static const size_t c_defaultSkippedFrameCount;
		size_t m_skippedFramesCount;
};
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::AbstractCallstack& callstack);

#endif
