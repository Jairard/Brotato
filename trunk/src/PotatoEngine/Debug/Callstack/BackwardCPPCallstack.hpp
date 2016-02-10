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

namespace Pot { namespace Debug
{
class BackwardCPPCallstack: public AbstractCallstack
{
	public:
		BackwardCPPCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount, bool hasRealTimeConstraint = false);
		virtual ~BackwardCPPCallstack();

		virtual const std::string& str() const;

	protected:
		virtual void setStackTrace(const std::string& other);

	private:
		void fetchCallstack();

	private:
		std::string m_trace;
};
}}
#endif

#endif
