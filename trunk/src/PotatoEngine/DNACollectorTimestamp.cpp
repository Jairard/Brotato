#include "DNACollectorTimestamp.hpp"

#include <limits>
#include <sstream>
#include "Debug/assert.hpp"

namespace Pot
{
	const potu64 DNACollectorTimestamp::c_invalidValue = std::numeric_limits<potu64>::max();
	const DNACollectorTimestamp DNACollectorTimestamp::c_invalid = DNACollectorTimestamp(c_invalidValue);

	DNACollectorTimestamp::DNACollectorTimestamp():
		m_value(0)
	{}

	DNACollectorTimestamp::DNACollectorTimestamp(const DNACollectorTimestamp& other):
		m_value(other.m_value)
	{}

	DNACollectorTimestamp::DNACollectorTimestamp(potu64 value):
		m_value(value)
	{}

	DNACollectorTimestamp& DNACollectorTimestamp::operator++()
	{
		++m_value;
		
		if (!isValid())
		{
			std::ostringstream oss;
			oss << "Max DNACollectorTimestamp value reached (" << c_invalidValue << "). ";
			oss << "Either you are developing quite a big game or this engine is fucked up.";
			ASSERT_RELEASE_MSG(isValid(), oss.str().c_str());
		}

		return *this;
	}

	DNACollectorTimestamp DNACollectorTimestamp::operator++(int depr)
	{
		UNUSED(depr);
		DNACollectorTimestamp tmp(*this);
		++(*this);
		return tmp;
	}

	bool DNACollectorTimestamp::operator<(const DNACollectorTimestamp& other) const
	{
		return m_value < other.m_value;
	}

	bool DNACollectorTimestamp::operator==(const DNACollectorTimestamp& other) const
	{
		return value() == other.value();
	}
	
	bool DNACollectorTimestamp::isValid() const
	{
		return m_value != c_invalidValue;
	}

	void DNACollectorTimestamp::invalidate()
	{
		m_value = c_invalidValue;
		ASSERT_DEBUG(!isValid());
	}
}

std::ostream& operator<<(std::ostream& stream, const Pot::DNACollectorTimestamp& timestamp)
{
	stream << "DNACollectorTimestamp(" << timestamp.value() << ")";
	return stream;
}
