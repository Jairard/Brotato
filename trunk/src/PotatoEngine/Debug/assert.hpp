#ifndef __POT_DEBUG_ASSERT__
#define __POT_DEBUG_ASSERT__

#include "../Core/CompilFlags.hpp"

#define ASSERT_RELEASE(test)           ASSERT_RELEASE_MSG(test, "")
#define ASSERT_RELEASE_MSG(test, msg)  { if (!(test)) assertTest(#test, msg, __FILE__, __LINE__, __PRETTY_FUNCTION__); }
#define ASSERT_NOT_REACHED()           ASSERT_NOT_REACHED_MSG("")
#define ASSERT_NOT_REACHED_MSG(msg)    assertNotReached(msg, __FILE__, __LINE__, __PRETTY_FUNCTION__);
#define ASSERT_NOT_IMPLEMENTED()       assertNotImplemented(__FILE__, __LINE__, __PRETTY_FUNCTION__);

#ifdef POT_DEBUG
# define ASSERT_DEBUG(test)            ASSERT_RELEASE(test)
# define ASSERT_DEBUG_MSG(test, msg)   ASSERT_RELEASE_MSG(test, msg)
#else
# define ASSERT_DEBUG(test)            ASSERT_RELEASE(test)
# define ASSERT_DEBUG_MSG(test, msg)
#endif

namespace Pot
{
	void assertTest(const char* test, const char* msg, const char* file, long line, const char* function);
	void assertNotReached(const char* msg, const char* file, long line, const char* function);
	void assertNotImplemented(const char* file, long line, const char* function);
	void assertImpl(const char* msg, const char* file, long line, const char* function);
}

#endif
