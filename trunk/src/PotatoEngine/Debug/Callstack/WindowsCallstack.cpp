#include "../../stdafx.h"
#include "WindowsCallstack.hpp"

#ifdef POT_WINDOWS_CALLSTACK_SUPPORT
#include <string>
#include <DbgHelp.h>
#include "../Logger.hpp"

namespace Pot { namespace Debug
{
    WindowsCallstack::WindowsCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
        AbstractCallstack(skippedFrameCount, hasRealTimeConstraint),
        m_trace()
    {
        fetchCallstack();
    }

    WindowsCallstack::~WindowsCallstack()
    {}

    const std::string& WindowsCallstack::str() const
    {
        return m_trace;
    }

    void WindowsCallstack::fetchCallstack()
    {
        HANDLE process = GetCurrentProcess();
        SymInitialize(process, nullptr, true);

        CONTEXT context;
        memset(&context, 0, sizeof(CONTEXT));
        context.ContextFlags = CONTEXT_FULL;

        // Load the RTLCapture context function:
        HINSTANCE kernel32 = LoadLibrary(L"Kernel32.dll");
        typedef void (*RtlCaptureContextFunc)(CONTEXT* ContextRecord);
        RtlCaptureContextFunc rtlCaptureContext = (RtlCaptureContextFunc)GetProcAddress(kernel32, "RtlCaptureContext");

        // Capture the thread context
        rtlCaptureContext(&context);

#if defined(POT_ARCH_64)
        const DWORD64 address = context.Rip;
#elif defined(POT_ARCH_32)
        const DWORD address = context.Eip;
#else
        const DWORD address = context.Eip; // Fallback
#endif

        STACKFRAME frame;
        memset(&frame, 0, sizeof(STACKFRAME));
        // setup initial stack frame
        frame.AddrPC.Offset    = address;
        frame.AddrPC.Mode      = AddrModeFlat;
        frame.AddrStack.Offset = address;
        frame.AddrStack.Mode   = AddrModeFlat;
        frame.AddrFrame.Offset = address;
        frame.AddrFrame.Mode   = AddrModeFlat;

        const DWORD machineType = IMAGE_FILE_MACHINE_I386; // | IMAGE_FILE_MACHINE_IA64 | IMAGE_FILE_MACHINE_AMD64

        while (StackWalk(machineType,
            process,
            GetCurrentThread(),
            &frame,
            &context,
            nullptr,
            SymFunctionTableAccess,
            SymGetModuleBase,
            nullptr))
        {
#ifdef POT_COMPILER_MSC

#if defined(POT_ARCH_64)
            DWORD64 displacement = 0;
            DWORD64 address = frame.AddrPC.Offset;
#elif defined(POT_ARCH_32)
            DWORD displacement = 0;
            DWORD address = frame.AddrPC.Offset;
#else
            DWORD displacement = 0;
            DWORD address = frame.AddrPC.Offset;
#endif

            const size_t nameSize = 256;
            char symbolBuffer[sizeof(IMAGEHLP_SYMBOL) + nameSize];
            memset(symbolBuffer, 0, sizeof(IMAGEHLP_SYMBOL) + nameSize);
            // Cast it to a symbol struct:
            IMAGEHLP_SYMBOL* pSymbol = (IMAGEHLP_SYMBOL*)symbolBuffer;
            // Need to set the first two fields of this symbol before obtaining name info:
            pSymbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL) + nameSize;
            pSymbol->MaxNameLength = nameSize - 1;

            if (SymGetSymFromAddr(process, address, &displacement, pSymbol))
                Logger::log(Logger::CWarning, "symbol: %s", pSymbol->Name);
            else
                Logger::log(Logger::CWarning, "SymGetSymFromAddr failed on %#p", address);

            //AbstractCallstack::outputFileAndLineFromAddress((void*)address, std::string());
            Logger::log(Logger::CWarning, "addr2line");
#endif
        }

        SymCleanup(process);
    }
}}
#endif
