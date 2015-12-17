#include "StackWalkerCallstack.hpp"

#ifdef POT_STACKWALKER_SUPPORT
#include <iomanip>
#include <sstream>
#include "../Logger.hpp"
#include "StackWalker.h"

namespace Pot { namespace Debug
{
    StackWalkerCallstack::StackWalkerCallstack(size_t skippedFrameCount):
        AbstractCallstack(skippedFrameCount + 1),
        StackWalker(),
        m_trace(),
        m_traceStream(),
        m_currentFrame(0)
    {
        fetchCallstack();
    }

    StackWalkerCallstack::~StackWalkerCallstack()
    {}

    const std::string& StackWalkerCallstack::str() const
    {
        return m_trace;
    }

    void StackWalkerCallstack::OnCallstackEntry(CallstackEntryType eType, CallstackEntry& entry)
    {
        // Don't call parent, we want to totally redefine behaviour here
        if (eType == lastEntry || entry.offset == 0)
            return;

        if (++m_currentFrame < m_skippedFramesCount)
            return;

        if (!isStringSet(entry.name))
            strcpy_s(entry.name, "[function name not available]");
        if (!isStringSet(entry.undName))
            strcpy_s(entry.name, entry.undName);
        if (!isStringSet(entry.undFullName))
            strcpy_s(entry.name, entry.undFullName);

        m_traceStream << "[" << std::setw(3) << std::right << m_currentFrame << "] "
                      << entry.undFullName
                      << " at " << (isStringSet(entry.lineFileName) ? entry.lineFileName : "[file name not available]") << ":" << entry.lineNumber;

        if (isStringSet(entry.moduleName))
            m_traceStream << " (in " << entry.moduleName << ")";

        m_traceStream << std::endl;
    }

    void StackWalkerCallstack::OnOutput(LPCSTR szText)
    {
        // Cancel parent output (to not be annoyed by symbols loading and other stuff)
    }

    void StackWalkerCallstack::fetchCallstack()
    {
        //*
        ShowCallstack();
        m_trace = m_traceStream.str();
        /*/
        StackWalker sw;
        sw.ShowCallstack();
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

        STACKFRAME frame;
        memset(&frame, 0, sizeof(STACKFRAME));
        // setup initial stack frame
        frame.AddrPC.Offset    = context.Eip;
        frame.AddrPC.Mode      = AddrModeFlat;
        frame.AddrStack.Offset = context.Esp;
        frame.AddrStack.Mode   = AddrModeFlat;
        frame.AddrFrame.Offset = context.Ebp;
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
            DWORD displacement = 0;
            DWORD address = frame.AddrPC.Offset;

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
#else
            addr2line(c_programName, static_cast<void*>(frame.AddrPC.Offset));
#endif
        }

        SymCleanup(process);
        //*/
    }

    bool StackWalkerCallstack::isStringSet(CHAR str[])
    {
        return strlen(str) > 0;
    }
}}

#endif
