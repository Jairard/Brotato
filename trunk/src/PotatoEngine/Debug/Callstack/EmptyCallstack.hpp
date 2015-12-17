#ifndef __POT_EMPTY_CALLSTACK__
#define __POT_EMPTY_CALLSTACK__

#include <string>
#include <ostream>
#include "AbstractCallstack.hpp"

namespace Pot { namespace Debug
{
class EmptyCallstack : public AbstractCallstack
{
	public:
		EmptyCallstack(size_t skippedFrameCount = 0);
		virtual ~EmptyCallstack();

		virtual const std::string& str() const;

	private:
		static const std::string c_message;
};
}}

#endif
