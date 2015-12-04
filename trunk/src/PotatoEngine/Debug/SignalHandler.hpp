#ifndef __POT_DEBUG_SIGNAL_HANDLER__
#define __POT_DEBUG_SIGNAL_HANDLER__

#include "PosixSignalHandler.hpp"

namespace Pot { namespace Debug
{
#ifdef POT_POSIX_SUPPORT
typedef PosixSignalHandler SignalHandler;
#else
#pragma message("No signal handler implementation")
#endif
}}

#endif
