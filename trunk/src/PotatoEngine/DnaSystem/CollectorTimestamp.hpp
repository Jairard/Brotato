#ifndef __POT_DNA_COLLECTOR_TIMESTAMP__
#define __POT_DNA_COLLECTOR_TIMESTAMP__

#include <ostream>
#include <Core/Tools.hpp>
#include <Core/types.hpp>

namespace Pot { namespace DnaSystem
{
	class CollectorTimestamp
	{
		public:
			CollectorTimestamp();
			CollectorTimestamp(const CollectorTimestamp& other);

			CollectorTimestamp& operator++();         // ++(*this)
			CollectorTimestamp  operator++(int depr); // (*this)++
			bool operator<(const CollectorTimestamp& other) const;
			bool operator==(const CollectorTimestamp& other) const;

			bool isValid() const;
			void invalidate();
			potu64 value() const { return m_value; }

		private:
			CollectorTimestamp(potu64 value); // Used to build c_invalid

		public:
			static const CollectorTimestamp c_invalid;

		private:
			static const potu64 c_invalidValue;
			potu64 m_value;
	};
}}

namespace std
{
	template <>
	struct hash<Pot::DnaSystem::CollectorTimestamp>
	{
		size_t operator()(const Pot::DnaSystem::CollectorTimestamp& timestamp) const
		{
			return hash<potu64>()(timestamp.value());
		}
	};
}

std::ostream& operator<<(std::ostream& stream, const Pot::DnaSystem::CollectorTimestamp& timestamp);

#endif
