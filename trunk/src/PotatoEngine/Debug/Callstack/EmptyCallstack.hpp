#ifndef __POT_EMPTY_CALLSTACK__
#define __POT_EMPTY_CALLSTACK__

#include <ostream>
#include <string>
#include <Debug/Callstack/AbstractCallstack.hpp>

namespace Pot { namespace Debug
{
class EmptyCallstack : public AbstractCallstack
{
	public:
		EmptyCallstack(size_t sizetDummy = 0, bool boolDummy = false);
		virtual ~EmptyCallstack();

		virtual const std::string& str() const;

	protected:
		virtual void setStackTrace(const std::string& trace);

	private:
		static const std::string c_message;
};
}}

#endif
