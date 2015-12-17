#include "../stdafx.h"
#include "SignalHandler.hpp"

#include <sstream>
#include "../Core/compil.hpp"
#include "assert.hpp"
#include "Logger.hpp"
#include "PosixSignalHandler.hpp"
#include "WindowsSignalHandler.hpp"

namespace Pot { namespace Debug
{
    const char* SignalHandler::c_programName = "<undefined>";
#ifdef POT_DEBUG
    bool SignalHandler::s_initialized = false;
#endif

    void SignalHandler::setup()
    {
#ifdef POT_DEBUG
        if (s_initialized)
        {
            Logger::log(Logger::CWarning, "Trying to initialize signal handling twice ! This call of SignalHandler::setup() will be ignored");
            return;
        }
        s_initialized = true;
#endif

#if defined(POT_PLATFORM_WINDOWS)
        WindowsSignalHandler::setup();
#elif defined(POT_POSIX_SUPPORT)
        PosixSignalHandler::setup();
#else
#pragma message("No signal handler implementation")
#endif
    }

    void SignalHandler::setProgramName(const char* name)
    {
        ASSERT_DEBUG(name != nullptr);

        if (c_programName != nullptr)
        {
            std::ostringstream oss;
            oss << "SignalHandler: trying to set program name twice !"
                << " (" << c_programName << " -> " << name << ")";
            ASSERT_DEBUG_MSG(c_programName == nullptr, oss.str().c_str());
            return;
        }

        c_programName = name;
    }

    const char* SignalHandler::programName()
    {
        ASSERT_DEBUG(c_programName != nullptr);
        return c_programName;
    }
}}
