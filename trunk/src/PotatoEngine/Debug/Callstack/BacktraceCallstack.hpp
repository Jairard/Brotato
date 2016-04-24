#ifndef __POT_DEBUG_BACKTRACE_CALLSTACK__
#define __POT_DEBUG_BACKTRACE_CALLSTACK__

#include <Core/compil.hpp>

#ifdef POT_COMPILER_GCC
#define POT_BACKTRACE_SUPPORT
#endif

#ifdef POT_BACKTRACE_SUPPORT
#include <ostream>
#include <string>
#include <Debug/Callstack/AbstractCallstack.hpp>

namespace Pot { namespace Debug
{
class BacktraceCallstack: public AbstractCallstack
{
	public:
		BacktraceCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount, bool hasRealTimeConstraint = false);
		virtual ~BacktraceCallstack();

		virtual const std::string& str() const;

	private:
		void fetchCallstack();

	private:
		std::string m_trace;
};
}}
#endif

#endif
