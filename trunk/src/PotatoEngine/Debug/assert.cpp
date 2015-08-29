#include <iostream>

#include <assert.h>
#include <sstream>
#include <cstring>
#include "assert.hpp"
#include "Logger.hpp"

namespace Pot
{
	using Debug::Logger;
	
	void assertTest(const char* test, const char* msg, const char* file, long line, const char* function)
	{
		std::ostringstream oss;
		oss << "test '" << test << "' failed";
		if (strlen(msg) > 0)
			oss << " (" << msg << ")";
		assertImpl(oss.str().c_str(), file, line, function);
	}
	
	void assertNotReached(const char* msg, const char* file, long line, const char* function)
	{
		std::ostringstream oss;
		oss << "not reached";
		if (strlen(msg) > 0)
			oss << " (" << msg << ")";
		assertImpl(oss.str().c_str(), file, line, function);
	}
	
	void assertNotImplemented(const char* file, long line, const char* function)
	{
		assertImpl("not implemented", file, line, function);
	}
	
	void assertImpl(const char* msg, const char* file, long line, const char* function)
	{
		Logger::log(Logger::CAssert, "%s:%lu: Assert in %s: %s", file, line, function, msg);
		assert(false);
	}
}
