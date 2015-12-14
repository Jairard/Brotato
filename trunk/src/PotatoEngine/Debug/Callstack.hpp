#ifndef __POT_DEBUG_CALLSTACK__
#define __POT_DEBUG_CALLSTACK__

#include "Callstack/EmptyCallstack.hpp"
#include "Callstack/BacktraceCallstack.hpp"
#include "Callstack/BackwardCPPCallstack.hpp"

namespace Pot { namespace Debug
{
#if defined(POT_BACKWARD_CPP_SUPPORT)
typedef BackwardCPPCallstack Callstack;
#elif defined(POT_BACKTRACE_SUPPORT)
typedef BacktraceCallstack Callstack;
#else
typedef EmptyCallstack Callstack;
#endif
}}

#endif