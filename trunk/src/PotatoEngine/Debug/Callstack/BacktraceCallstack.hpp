#ifndef __POT_DEBUG_BACKTRACE_CALLSTACK__
#define __POT_DEBUG_BACKTRACE_CALLSTACK__

#include <Core/compil.hpp>

#ifdef POT_COMPILER_GCC
#define POT_BACKTRACE_SUPPORT
#endif

#ifdef POT_BACKTRACE_SUPPORT
#include <dlfcn-compat.h>
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

	protected:
		virtual void init();
		virtual void cleanUp();

		virtual void* fetchNextEntry(const size_t index);
		virtual bool fetchSymbolName(const void* const address, std::string& outSymbolName) const;
		virtual bool fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const;
		virtual bool fetchBinaryName(const void* const address, std::string& outBinaryName) const;

	private:
		size_t m_frameCount;
		void** m_adresses;
		char** m_symbols;
		Dl_info m_currentInfo;
		size_t m_currentFrame;
		bool m_dlAddrSuccess;
};
}}
#endif

#endif
