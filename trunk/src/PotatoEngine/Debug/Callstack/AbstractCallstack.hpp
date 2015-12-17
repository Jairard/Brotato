#ifndef __POT_DEBUG_ABSTRACT_CALLSTACK__
#define __POT_DEBUG_ABSTRACT_CALLSTACK__

#include <string>
#include <ostream>

namespace Pot { namespace Debug
{
class AbstractCallstack
{
	public:
		AbstractCallstack(size_t skippedFrameCount, bool hasRealTimeConstraint);
		virtual ~AbstractCallstack();

		void operator=(const AbstractCallstack& other);
		const char* operator()() const;
		const char* c_str() const;
		virtual const std::string& str() const = 0;

		static void setProgramName(const char* name);
		static std::string& outputFileAndLineFromAddress(const void* const address, std::string& outString, bool realTimeConstraint = false);

	protected:
		std::string& getFileAndLine_internal(const void* address, std::string& outString) const;
		virtual void setStackTrace(const std::string& trace) = 0;

	private:
		static void formatFileAndLine(char buffer[]);

	public:
		static const size_t c_defaultSkippedFrameCount;

	protected:
		static const char* c_programName;
		static const size_t c_maxFrameCount;
		size_t m_skippedFrameCount;

	private:
		bool m_hasRealTimeConstraint;
};
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::AbstractCallstack& callstack);

#endif
