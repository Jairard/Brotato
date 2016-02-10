#include <stdafx.h>
#include "BackwardCPPCallstack.hpp"

#ifdef POT_BACKWARD_CPP_SUPPORT

#include <sstream>
#include <Debug/Callstack/backward.hpp>
#include <Debug/Logger.hpp>

// Will only work on Unix platforms
namespace backward
{
	SignalHandling sh;
}

namespace Pot { namespace Debug
{
	BackwardCPPCallstack::BackwardCPPCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
		AbstractCallstack(skippedFrameCount, hasRealTimeConstraint),
		m_trace()
	{
		fetchCallstack();
	}

	BackwardCPPCallstack::~BackwardCPPCallstack()
	{}

	const std::string& BackwardCPPCallstack::str() const
	{
		return m_trace;
	}

	void BackwardCPPCallstack::setStackTrace(const std::string& trace)
	{
		m_trace = trace;
	}

	void BackwardCPPCallstack::fetchCallstack()
	{
		backward::StackTrace stack;
		stack.load_here(c_maxFrameCount);
		const size_t frameCount = stack.size();

		backward::TraceResolver solver;
		solver.load_stacktrace(stack);

		std::ostringstream oss;
		// TODO: add code snippet for first non-skipped frame

		for (size_t i = m_skippedFrameCount; i < frameCount; ++i)
		{
			if (i > m_skippedFrameCount)
				oss << std::endl;

			backward::ResolvedTrace trace = solver.resolve(stack[i]);
			
			oss << "[" << std::setw(3) << std::right << i << "] "
			    << std::setw(50) << std::left << trace.source.function
			    << " at " << trace.source.filename << ":" << trace.source.line << ", " << trace.source.col
			    << " (in " << trace.object_filename << ")";
		}

		if (frameCount == c_maxFrameCount)
			oss << std::endl << "[possibly truncated]";

		m_trace = oss.str();
	}
}}
#endif
