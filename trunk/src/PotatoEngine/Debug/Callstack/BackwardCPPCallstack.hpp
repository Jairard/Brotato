#ifndef __POT_BACKWARD_CPP_CALLSTACK__
#define __POT_BACKWARD_CPP_CALLSTACK__

#include <Core/compil.hpp>

#ifdef POT_PLATFORM_LINUX
#define POT_BACKWARD_CPP_SUPPORT
#endif

#ifdef POT_BACKWARD_CPP_SUPPORT
// from https://github.com/bombela/backward-cpp
// (not tested yet, need Linux compil for that)

#include <string>
#include <Debug/Callstack/AbstractCallstack.hpp>
#include <Debug/Callstack/backward.hpp>

namespace Pot { namespace Debug
{
class BackwardCPPCallstack: public AbstractCallstack
{
	public:
		BackwardCPPCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount, bool hasRealTimeConstraint = false);
		virtual ~BackwardCPPCallstack();

	protected:
		virtual void init();

		virtual void* fetchNextEntry(const size_t index);
		virtual bool fetchSymbolName(const void* const address, std::string& outSymbolName) const;
		virtual bool fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const;
		virtual bool fetchBinaryName(const void* const address, std::string& outBinaryName) const;

	private:
		backward::StackTrace m_trace;
		backward::TraceResolver m_solver;
		backward::ResolvedTrace m_resolvedTrace;
		size_t m_frameCount;
};
}}
#endif

#endif
