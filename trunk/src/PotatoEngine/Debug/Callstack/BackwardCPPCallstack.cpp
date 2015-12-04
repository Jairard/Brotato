#include "../../stdafx.h"
#include "BackwardCPPCallstack.hpp"

#ifdef POT_BACKWARD_CPP_SUPPORT

#include <sstream>
#include "backward.hpp"
#include "Logger.hpp"

// Will only work on Unix platforms
namespace backward
{
	SignalHandling sh;
}

namespace Pot { namespace Debug
{
	BackwardCPPCallstack::BackwardCPPCallstack(size_t skippedFrameCount):
		AbstractCallstack(skippedFrameCount),
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

	const char* BackwardCPPCallstack::c_str() const
	{
		return m_trace.c_str();
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

		for (size_t i = m_skippedFramesCount; i < frameCount; ++i)
		{
			backward::ResolvedTrace trace = solver.resolve(stack[i]);
			
			oss << "[" << std::setw(3) << std::right << i << "] "
			    << std::setw(50) << std::left << trace.source.function
			    << " at " << trace.source.filename << ":" << trace.source.line << ", " << trace.source.col
			    << " (in " << trace.object_filename << ")"
			    << std::endl;
		}

		if (frameCount == c_maxFrameCount)
			oss << "[possibly truncated]" << std::endl;

		m_trace.assign(oss.str());
	}
}}
#endif
