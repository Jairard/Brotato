#ifndef __POT_DEBUG_SIGNAL_HANDLER__
#define __POT_DEBUG_SIGNAL_HANDLER__

#include <Core/NonInstantiable.hpp>
#include <Debug/PosixSignalHandler.hpp>

namespace Pot { namespace Debug
{
    class SignalHandler: public NonInstantiable
    {
    public:
        static void setup();
        static void setProgramName(const char* name);
        static const char* programName();

    private:
        static const char* c_programName;

#ifdef POT_DEBUG
    private:
        static bool s_initialized;
#endif
    };
}}

#endif
