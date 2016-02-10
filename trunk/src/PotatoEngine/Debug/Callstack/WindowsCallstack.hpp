#ifndef __POT_WINDOWS_CALLSTACK__
#define __POT_WINDOWS_CALLSTACK__

#include "../../Core/compil.hpp"

#ifdef POT_PLATFORM_WINDOWS
#define POT_WINDOWS_CALLSTACK_SUPPORT
#endif

#ifdef POT_WINDOWS_CALLSTACK_SUPPORT
#include <string>
#include "AbstractCallstack.hpp"

namespace Pot { namespace Debug
{
class WindowsCallstack: public AbstractCallstack
{
    public:
        WindowsCallstack(size_t skippedFrameCount = AbstractCallstack::c_defaultSkippedFrameCount, bool hasRealTimeConstraint = false);
        virtual ~WindowsCallstack();

        virtual const std::string& str() const;

    private:
        void fetchCallstack();

    private:
        std::string m_trace;
};
}}
#endif

#endif
