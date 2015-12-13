#include "SignalHandler.hpp"

#include <signal.h>
#include <csignal>
#include <cerrno>
#include "../Core/Tools.hpp"
#include "assert.hpp"
#include "Logger.hpp"
#include "Callstack.hpp"

namespace Pot { namespace Debug
{
	const size_t SignalHandler::c_additionalFramesToSkip = 3;

	// List from backward.hpp
	const SignalHandler::SignalInfo SignalHandler::c_handledSignals[] = {
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
	const size_t SignalHandler::c_signalCount = sizeof(SignalHandler::c_handledSignals) / sizeof(SignalHandler::c_handledSignals[0]);
	potb SignalHandler::s_alternateStack[SIGSTKSZ];
#ifdef POT_DEBUG
	bool SignalHandler::s_initialized = false;
#endif

	// Inspired form http://spin.atomicobject.com/2013/01/13/exceptions-stack-traces-c/
	void SignalHandler::setupSignalHandling()
	{
#ifdef POT_DEBUG
		if (s_initialized)
		{
			Logger::log(Logger::CWarning,"Trying to initialize signal handling twice ! This call of handleSignals_c99 will be ignored");
			return;
		}
#endif

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

#ifdef __APPLE__
		// for some reason we backtrace() doesn't work on OSX
		// when we use an alternate stack, so this is meaningless
		action.sa_flags = SA_SIGINFO;
#else
		action.sa_flags = SA_SIGINFO | SA_ONSTACK;
#endif

		for (size_t i = 0; i < c_signalCount; ++i)
		{
			if (sigaction(c_handledSignals[i].id, &action, nullptr) != 0)
				Logger::log(Logger::CWarning, "setupSignalHandling: sigaction failed for %s", c_handledSignals[i].name);
		}

#ifdef POT_DEBUG
		s_initialized = true;
#endif
	}

	void SignalHandler::handleSignal(int signalId, siginfo_t* info, void* context)
	{
		UNUSED(info);
		UNUSED(context);

		const char* name = "UNKNOWN";
		size_t framesToSkip = AbstractCallstack::c_defaultSkippedFrameCount + c_additionalFramesToSkip;

		for (size_t i = 0; i < c_signalCount; ++i)
		{
			if (c_handledSignals[i].id == signalId)
			{
				name = c_handledSignals[i].name;
				break;
			}
		}

		if (signalId == SIGABRT)
			framesToSkip += 5;

		framesToSkip = 0;
		// This callstack is not nice on OSX (and Windows ?) ...
		Logger::log(Logger::CError, "Signal %s was triggered.\n%s", name, Callstack(framesToSkip)());
		exit(EXIT_FAILURE);
	}
}}
