#ifndef __POT_DNA_COLLECTOR_TIMESTAMP__
#define __POT_DNA_COLLECTOR_TIMESTAMP__

#include <ostream>
#include "../Core/types.hpp"
#include "../Core/Tools.hpp"

namespace Pot
{
	class DNACollectorTimestamp
	{
		public:
			DNACollectorTimestamp();
			DNACollectorTimestamp(const DNACollectorTimestamp& other);

			DNACollectorTimestamp& operator++();         // ++(*this)
			DNACollectorTimestamp  operator++(int depr); // (*this)++
			bool operator<(const DNACollectorTimestamp& other) const;
			bool operator==(const DNACollectorTimestamp& other) const;

			bool isValid() const;
			void invalidate();
			potu64 value() const { return m_value; }

		private:
			DNACollectorTimestamp(potu64 value); // Used to build c_invalid

		public:
			static const DNACollectorTimestamp c_invalid;

		private:
			static const potu64 c_invalidValue;
			potu64 m_value;
	};
}

namespace std
{
	template <>
	struct hash<Pot::DNACollectorTimestamp>
	{
		size_t operator()(const Pot::DNACollectorTimestamp& timestamp) const
		{
			return hash<potu64>()(timestamp.value());
		}
	};
}

std::ostream& operator<<(std::ostream& stream, const Pot::DNACollectorTimestamp& timestamp);

#endif
