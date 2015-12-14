#ifndef __POT_DEBUG_POSIX_SIGNAL_HANDLER__
#define __POT_DEBUG_POSIX_SIGNAL_HANDLER__

#include "../Core/compil.hpp"

#ifndef POT_COMPILER_MSC
#define POT_POSIX_SUPPORT
#endif

#ifdef POT_POSIX_SUPPORT

#include <cstddef>
#include <signal.h>
#include <csignal>
#include <cerrno>
#include "../Core/compil.hpp"
#include "../Core/types.hpp"
#include "../Core/NonInstantiable.hpp"

namespace Pot { namespace Debug
{
    class PosixSignalHandler: public NonInstantiable
    {
    private:
        struct SignalInfo
        {
            int id;
            const char* name;
        };

    public:
        static void setupSignalHandling();

    private:
        static void handleSignal(int signalId, siginfo_t* info, void* context);

    private:
        static const size_t c_additionalFramesToSkip;
        static const SignalInfo c_handledSignals[];
        static const size_t c_signalCount;
        static potb s_alternateStack[SIGSTKSZ];
#ifdef POT_DEBUG
        static bool s_initialized;
#endif
    };
}}
#endif

#endif
