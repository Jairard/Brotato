#ifndef __POT_DEBUG_BACKTRACE_CALLSTACK__
#define __POT_DEBUG_BACKTRACE_CALLSTACK__

#ifdef __GNUC__
#define POT_BACKTRACE_SUPPORT
#endif

#ifdef POT_BACKTRACE_SUPPORT
#include <string>
#include <ostream>
#include "AbstractCallstack.hpp"

namespace Pot { namespace Debug
{
class BacktraceCallstack: public AbstractCallstack
{
	public:
		BacktraceCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount);
		virtual ~BacktraceCallstack();

		virtual const std::string& str() const;
		virtual const char* c_str() const;

	private:
		void fetchCallstack();
		std::string& getFileAndLine(const void* const address, std::string& outString);
		void formatFileAndLine(char buffer[]);

	private:
		std::string m_trace;
};
}}
#endif

#endif
