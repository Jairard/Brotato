#ifndef __POT_DEBUG_ABSTRACT_CALLSTACK__
#define __POT_DEBUG_ABSTRACT_CALLSTACK__

#include <ostream>
#include <string>
#include <vector>

namespace Pot { namespace Debug
{

struct CallStackEntry
{
	size_t m_index;
	const void* m_address;
	std::string m_symbolName;
	std::string m_fileName;
	size_t m_line;
	std::string m_binaryName;
};

class AbstractCallstack
{
	public:
		AbstractCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint);
		virtual ~AbstractCallstack();

		const char* operator()() const;
		const char* c_str() const;
		const std::string& str() const;
		const std::vector<CallStackEntry>& entries() const;

		static void setProgramName(const char* name);
		static void enableFrameSkipping();
		static void forbidFrameSkipping();
		static std::string& outputFileAndLineFromAddress(const void* const address, std::string& outString, bool realTimeConstraint = false);

	protected:
		bool hasRealTimeConstraint() const;
		virtual void init();
		virtual void cleanUp();

		void fetchCallstack();
		virtual void* fetchNextEntry(const size_t index) = 0;
		virtual bool fetchSymbolName(const void* const address, std::string& outSymbolName) const = 0;
		virtual bool fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const = 0;
		virtual bool fetchBinaryName(const void* const address, std::string& outBinaryName) const = 0;

	private:
		static void formatFileAndLine(char buffer[]);

	public:
		static const size_t c_defaultSkippedFrameCount;

	protected:
		static const char* c_programName;
		static const size_t c_maxFrameCount;
		size_t m_skippedFrameCount;

	private:
		static bool s_canSkipFrames;
		bool m_hasRealTimeConstraint;
		std::vector<CallStackEntry> m_entries;
		std::string m_trace;
};
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::AbstractCallstack& callstack);

#endif
