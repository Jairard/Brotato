#ifndef __POT_DEBUG_CALLSTACK__
#define __POT_DEBUG_CALLSTACK__

#include <Debug/Callstack/BacktraceCallstack.hpp>
#include <Debug/Callstack/BackwardCPPCallstack.hpp>
#include <Debug/Callstack/EmptyCallstack.hpp>
#include <Debug/Callstack/WindowsCallstack.hpp>

namespace Pot { namespace Debug
{
#if defined(POT_BACKWARD_CPP_SUPPORT)
typedef BackwardCPPCallstack Callstack;
#elif defined(POT_BACKTRACE_SUPPORT)
typedef BacktraceCallstack Callstack;
#elif defined(POT_WINDOWS_CALLSTACK_SUPPORT)
typedef WindowsCallstack Callstack;
#else
typedef EmptyCallstack Callstack;
#endif
}}

#endif
