#ifndef __POT_DEBUG_WINDOWS_SIGNAL_HANDLER__
#define __POT_DEBUG_WINDOWS_SIGNAL_HANDLER__

#include "../Core/compil.hpp"

#ifdef POT_PLATFORM_WINDOWS
#include <wtypes.h>
#include <string>
#include "../Core/NonInstantiable.hpp"

namespace Pot { namespace Debug
{
    class WindowsSignalHandler: public NonInstantiable
    {
    private:
        struct SignalInfo
        {
            DWORD id;
            const char* name;
        };

    public:
        static void setup();

    private:
        static LONG WINAPI exceptionHandler(EXCEPTION_POINTERS* exceptionInfo);
        static std::string& outputFileAndLine(const void* const address, std::string& outString);

    private:
        static const SignalInfo c_handledExceptions[];
        static const size_t c_exceptionCount;
    };
}}
#endif

#endif
