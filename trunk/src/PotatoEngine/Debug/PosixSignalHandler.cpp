#include <stdafx.h>
#include "PosixSignalHandler.hpp"

#ifdef POT_POSIX_SUPPORT
#include <cerrno>
#include <csignal>
#include <signal.h>

#include <Core/Tools.hpp>
#include <Debug/assert.hpp>
#include <Debug/Callstack.hpp>
#include <Debug/Logger.hpp>

namespace Pot { namespace Debug
{
	const size_t PosixSignalHandler::c_additionalFramesToSkip = 3;

	// List from backward.hpp
	const PosixSignalHandler::SignalInfo PosixSignalHandler::c_handledSignals[] = {
		{ SIGILL,    "SIGILL" },
		{ SIGABRT,   "SIGABRT" },
		{ SIGFPE,    "SIGFPE" },
		{ SIGSEGV,   "SIGSEGV" },
		{ SIGBUS,    "SIGBUS" },

		{ SIGHUP,    "SIGHUP" },
		{ SIGINT,    "SIGINT" },
		{ SIGPIPE,   "SIGPIPE" },
		{ SIGALRM,   "SIGALRM" },
		{ SIGTERM,   "SIGTERM" },
		{ SIGUSR1,   "SIGUSR1" },
		{ SIGUSR2,   "SIGUSR2" },
		//{ SIGPOLL,   "SIGPOLL" }, // Deprecated
		{ SIGPROF,   "SIGPROF" },
		{ SIGVTALRM, "SIGVTALRM" },
		{ SIGIO,     "SIGIO" },
		//{ SIGPWR,    "SIGPWR" }, // Deprecated

		{ SIGQUIT,   "SIGQUIT" },
		{ SIGSYS,    "SIGSYS" },
		{ SIGTRAP,   "SIGTRAP" },
		{ SIGXCPU,   "SIGXCPU" },
		{ SIGXFSZ,   "SIGXFSZ" }
	};

	const size_t PosixSignalHandler::c_signalCount = sizeof(PosixSignalHandler::c_handledSignals) / sizeof(PosixSignalHandler::c_handledSignals[0]);
	potb PosixSignalHandler::s_alternateStack[SIGSTKSZ];

	// Inspired form http://spin.atomicobject.com/2013/01/13/exceptions-stack-traces-c/
	void PosixSignalHandler::setup()
	{
		// Setup alternate stack
		stack_t ss = {};
		// malloc is usually used here, I'm not 100% sure my static allocation
		// is valid but it seems to work just fine.
		ss.ss_sp = reinterpret_cast<void*>(&s_alternateStack);
		ss.ss_size = SIGSTKSZ;
		ss.ss_flags = 0;

		errno = ENOENT;
		if (sigaltstack(&ss, nullptr) != 0)
			Logger::log(Logger::CWarning, "handlerSignals_posix: sigaltstack failed with error '%s'", strerror(errno));

		// Register signal handlers
		struct sigaction action = {};
		action.sa_sigaction = handleSignal;
		sigemptyset(&action.sa_mask);

#ifdef POT_PLATFORM_OSX
		// for some reason we backtrace() doesn't work on OSX
		// when we use an alternate stack, so this is meaningless
		action.sa_flags = SA_SIGINFO;
#else
		action.sa_flags = SA_SIGINFO | SA_ONSTACK;
	#endif

		for (size_t i = 0; i < c_signalCount; ++i)
		{
			const SignalInfo& info = c_handledSignals[i];
			if (sigaction(info.id, &action, nullptr) != 0)
				Logger::log(Logger::CWarning, "setupSignalHandling: sigaction failed for %s", info.name);
		}
	}

	void PosixSignalHandler::handleSignal(int signalId, siginfo_t* info, void* context)
	{
		POT_UNUSED(info);
		POT_UNUSED(context);

		const char* name = "UNKNOWN";
		size_t framesToSkip = AbstractCallstack::c_defaultSkippedFrameCount + c_additionalFramesToSkip;

		for (size_t i = 0; i < c_signalCount; ++i)
		{
			const SignalInfo& info = c_handledSignals[i];
			if (info.id == signalId)
			{
				name = info.name;
				break;
			}
		}

		if (signalId == SIGABRT)
			framesToSkip += 5;

		// This callstack is not nice on OSX ...
		Logger::log(Logger::CError, "Signal %s was triggered.\n%s", name, Callstack(framesToSkip)());
		exit(EXIT_FAILURE);
	}
}}
#endif
