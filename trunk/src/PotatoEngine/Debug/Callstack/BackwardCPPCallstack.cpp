#include <stdafx.h>
#include "BackwardCPPCallstack.hpp"

#ifdef POT_BACKWARD_CPP_SUPPORT
#include <sstream>

// Will only work on Unix platforms
namespace backward
{
	SignalHandling sh;
}

namespace Pot { namespace Debug
{
	BackwardCPPCallstack::BackwardCPPCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint):
		AbstractCallstack(skippedFrameCount, hasRealTimeConstraint),
		m_trace(),
		m_solver(),
		m_resolvedTrace(),
		m_frameCount(0)
	{
		init();
		fetchCallstack();
		cleanUp();
	}

	BackwardCPPCallstack::~BackwardCPPCallstack()
	{}

	void BackwardCPPCallstack::init()
	{
		AbstractCallstack::init();

		m_trace.load_here(c_maxFrameCount);
		m_solver.load_stacktrace(m_trace);
		m_frameCount = m_trace.size();
	}

	void* BackwardCPPCallstack::fetchNextEntry(const size_t index)
	{
		if (index >= m_frameCount)
			return nullptr;

		const backward::Trace& currentTrace = m_trace[index];
		m_resolvedTrace = m_solver.resolve(currentTrace);
		return currentTrace.addr;
	}

	bool BackwardCPPCallstack::fetchSymbolName(const void* const address, std::string& outSymbolName) const
	{
		POT_UNUSED(address);
		outSymbolName = m_resolvedTrace.source.function;
		return true;
	}

	bool BackwardCPPCallstack::fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const
	{
		POT_UNUSED(address);
		outFileName = m_resolvedTrace.source.filename;
		outLine = m_resolvedTrace.source.line;
		return true;
	}

	bool BackwardCPPCallstack::fetchBinaryName(const void* const address, std::string& outBinaryName) const
	{
		POT_UNUSED(address);
		outBinaryName = m_resolvedTrace.object_filename;
		return true;
	}
}}
#endif
