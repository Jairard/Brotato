#include <stdafx.h>
#include "CollectorTimestamp.hpp"

#include <limits>
#include <sstream>
#include <Core/types.hpp>
#include <Debug/assert.hpp>

namespace Pot { namespace DnaSystem
{
	const potu64 CollectorTimestamp::c_invalidValue = std::numeric_limits<potu64>::max();
	const CollectorTimestamp CollectorTimestamp::c_invalid = CollectorTimestamp(c_invalidValue);

	CollectorTimestamp::CollectorTimestamp():
		m_value(0)
	{}

	CollectorTimestamp::CollectorTimestamp(const CollectorTimestamp& other):
		m_value(other.m_value)
	{}

	CollectorTimestamp::CollectorTimestamp(potu64 value):
		m_value(value)
	{}

	CollectorTimestamp& CollectorTimestamp::operator++()
	{
		++m_value;
		
		if (!isValid())
		{
			std::ostringstream oss;
			oss << "Max CollectorTimestamp value reached (" << c_invalidValue << "). ";
			oss << "Either you are developing quite a big game or this engine is fucked up.";
			ASSERT_RELEASE_MSG(isValid(), oss.str().c_str());
		}

		return *this;
	}

	CollectorTimestamp CollectorTimestamp::operator++(int depr)
	{
		POT_UNUSED(depr);
		CollectorTimestamp tmp(*this);
		++(*this);
		return tmp;
	}

	bool CollectorTimestamp::operator<(const CollectorTimestamp& other) const
	{
		return m_value < other.m_value;
	}

	bool CollectorTimestamp::operator==(const CollectorTimestamp& other) const
	{
		return value() == other.value();
	}
	
	bool CollectorTimestamp::isValid() const
	{
		return m_value != c_invalidValue;
	}

	void CollectorTimestamp::invalidate()
	{
		m_value = c_invalidValue;
		ASSERT_DEBUG(!isValid());
	}
}}

std::ostream& operator<<(std::ostream& stream, const Pot::DnaSystem::CollectorTimestamp& timestamp)
{
	stream << "CollectorTimestamp(" << timestamp.value() << ")";
	return stream;
}
