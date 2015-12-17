#ifndef __POT_WINDOWS_CALLSTACK__
#define __POT_WINDOWS_CALLSTACK__

#include "../../Core/compil.hpp"

#if defined(POT_COMPILER_MSC) && (_MSC_VER >= 1100)
# define POT_STACKWALKER_SUPPORT
#endif

#ifdef POT_STACKWALKER_SUPPORT
#include <string>
#include <sstream>
#include "AbstractCallstack.hpp"
#include "StackWalker.h"

namespace Pot { namespace Debug
{
class StackWalkerCallstack: public AbstractCallstack, public StackWalker
{
	public:
		StackWalkerCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount);
		virtual ~StackWalkerCallstack();

		// AbstractCallstack
		virtual const std::string& str() const;

	protected:
		virtual void setStackTrace(const std::string& trace);

	private:
		// StackWalker
		virtual void OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry);
		virtual void OnOutput(LPCSTR szText);

		// Misc
		void fetchCallstack();
		bool isStringSet(CHAR str[]);

	private:
		std::string m_trace;
		std::ostringstream m_traceStream;
		size_t m_currentFrame;
};
}}
#endif

#endif
