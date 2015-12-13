#ifndef __POT_DEBUG_SIGNAL_HANDLER__
#define __POT_DEBUG_SIGNAL_HANDLER__

#include <cstddef>
#include <signal.h>
#include <csignal>
#include <cerrno>
#include "../Core/compilFlags.hpp"
#include "../Core/types.hpp"
#include "../Core/NonInstantiable.hpp"

// TODO:
// - Compatibility for Windows -> abstraction ?
namespace Pot { namespace Debug
{
	class SignalHandler: public NonInstantiable
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
