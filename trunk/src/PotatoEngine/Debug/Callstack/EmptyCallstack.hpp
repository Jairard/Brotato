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

	protected:
		virtual void* fetchNextEntry(const size_t index);
		virtual bool fetchSymbolName(const void* const address, std::string& outSymbolName) const;
		virtual bool fetchFileAndLine(const void* const address, std::string& outFileName, size_t& outLine) const;
		virtual bool fetchBinaryName(const void* const address, std::string& outBinaryName) const;
};
}}

#endif
