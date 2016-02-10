#ifndef __POT_DEBUG_POSIX_SIGNAL_HANDLER__
#define __POT_DEBUG_POSIX_SIGNAL_HANDLER__

#include <Core/compil.hpp>

#ifdef POT_POSIX_SUPPORT

#include <cerrno>
#include <csignal>
#include <cstddef>
#include <signal.h>
#include <Core/NonInstantiable.hpp>
#include <Core/types.hpp>

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
		static void setup();

	private:
		static void handleSignal(int signalId, siginfo_t* info, void* context);

	private:
		static const size_t c_additionalFramesToSkip;
		static const SignalInfo c_handledSignals[];
		static const size_t c_signalCount;
		static potb s_alternateStack[SIGSTKSZ];
	};
}}
#endif

#endif
