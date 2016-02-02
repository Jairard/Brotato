#include "../stdafx.h"
#include "WindowsSignalHandler.hpp"

#ifdef POT_PLATFORM_WINDOWS
#include <windows.h>
#include <sstream>
#include "assert.hpp"
#include "Logger.hpp"
#include "SignalHandler.hpp"
#include "Callstack.hpp"

namespace Pot { namespace Debug
{
    const WindowsSignalHandler::SignalInfo WindowsSignalHandler::c_handledExceptions[] = {
        { EXCEPTION_ACCESS_VIOLATION, "EXCEPTION_ACCESS_VIOLATION" },
        { EXCEPTION_ARRAY_BOUNDS_EXCEEDED, "EXCEPTION_ARRAY_BOUNDS_EXCEEDED" },
        { EXCEPTION_BREAKPOINT, "EXCEPTION_BREAKPOINT" },
        { EXCEPTION_DATATYPE_MISALIGNMENT, "EXCEPTION_DATATYPE_MISALIGNMENT" },
        { EXCEPTION_FLT_DENORMAL_OPERAND, "EXCEPTION_FLT_DENORMAL_OPERAND" },
        { EXCEPTION_FLT_DIVIDE_BY_ZERO, "EXCEPTION_FLT_DIVIDE_BY_ZERO" },
        { EXCEPTION_FLT_INEXACT_RESULT, "EXCEPTION_FLT_INEXACT_RESULT" },
        { EXCEPTION_FLT_INVALID_OPERATION, "EXCEPTION_FLT_INVALID_OPERATION" },
        { EXCEPTION_FLT_OVERFLOW, "EXCEPTION_FLT_OVERFLOW" },
        { EXCEPTION_FLT_STACK_CHECK, "EXCEPTION_FLT_STACK_CHECK" },
        { EXCEPTION_FLT_UNDERFLOW, "EXCEPTION_FLT_UNDERFLOW" },
        { EXCEPTION_ILLEGAL_INSTRUCTION, "EXCEPTION_ILLEGAL_INSTRUCTION" },
        { EXCEPTION_IN_PAGE_ERROR, "EXCEPTION_IN_PAGE_ERROR" },
        { EXCEPTION_INT_DIVIDE_BY_ZERO, "EXCEPTION_INT_DIVIDE_BY_ZERO" },
        { EXCEPTION_INT_OVERFLOW, "EXCEPTION_INT_OVERFLOW" },
        { EXCEPTION_INVALID_DISPOSITION, "EXCEPTION_INVALID_DISPOSITION" },
        { EXCEPTION_NONCONTINUABLE_EXCEPTION, "EXCEPTION_NONCONTINUABLE_EXCEPTION" },
        { EXCEPTION_PRIV_INSTRUCTION, "EXCEPTION_PRIV_INSTRUCTION" },
        { EXCEPTION_SINGLE_STEP, "EXCEPTION_SINGLE_STEP" },
        { EXCEPTION_STACK_OVERFLOW, "EXCEPTION_STACK_OVERFLOW" },
    };
    const size_t WindowsSignalHandler::c_exceptionCount = sizeof(WindowsSignalHandler::c_handledExceptions) / sizeof(WindowsSignalHandler::c_handledExceptions[0]);

    void WindowsSignalHandler::setup()
    {
        // Does nothing on VS, exception are already handled (maybe not all of them ?)
        SetUnhandledExceptionFilter(exceptionHandler);
    }

    LONG WINAPI WindowsSignalHandler::exceptionHandler(EXCEPTION_POINTERS* exceptionInfo)
    {
        ASSERT_RELEASE(exceptionInfo != nullptr);

        const DWORD code = exceptionInfo->ExceptionRecord->ExceptionCode;
        const char* exceptionName = "UNKNOWN_EXCEPTION";
        for (size_t i = 0; i < c_exceptionCount; ++i)
        {
            const SignalInfo& info = c_handledExceptions[i];
            if (info.id == code)
                exceptionName = info.name;
        }

        std::ostringstream oss;
        oss << "Exception " << exceptionName << " occured.";

        // If this is a stack overflow then we can't get the stack,
        // so just show where the error happened
        if (code != EXCEPTION_STACK_OVERFLOW)
            oss << std::endl << Callstack(0);
        else
        {
            std::string buffer;
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__)
			const void* addr = (void*)exceptionInfo->ContextRecord->Rip;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__)
			const void* addr = (void*)exceptionInfo->ContextRecord->Eip;
#else
#pragma(Arch is neither 32 nor 64 bits ?)
#endif
            oss << AbstractCallstack::outputFileAndLineFromAddress(addr, buffer, false);
        }

        Logger::log(Logger::CError, oss.str().c_str());
        return EXCEPTION_EXECUTE_HANDLER;
    }
}}
#endif
