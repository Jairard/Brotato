#include "AbstractCallstack.hpp"

#include <sstream>
#include "../assert.hpp"

namespace Pot { namespace Debug
{
	const char* AbstractCallstack::c_programName = nullptr;
	const size_t AbstractCallstack::c_maxFrameCount = 128;
	const size_t AbstractCallstack::c_defaultSkippedFrameCount = 3; // Maybe it'll be needed to specialize this constant

	AbstractCallstack::AbstractCallstack(size_t skippedFramesCount):
		m_skippedFramesCount(skippedFramesCount)
	{}

	AbstractCallstack::~AbstractCallstack()
	{}

	const char* AbstractCallstack::operator()() const
	{
		return c_str();
	}

	void AbstractCallstack::setProgramName(const char* name)
	{
		ASSERT_DEBUG(name != nullptr);

		if (c_programName != nullptr)
		{
			std::ostringstream oss;
			oss << "AbstractCallstack: trying to set program name twice !"
			    << " (" << c_programName << " -> " << name << ")";
			ASSERT_DEBUG_MSG(c_programName == nullptr, oss.str().c_str());
		}

		c_programName = name;
	}
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::AbstractCallstack& callstack)
{
	stream << callstack.str();
	return stream;
}
