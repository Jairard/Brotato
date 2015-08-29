#ifndef __POT_CORE_NONCOPYABLE__
#define __POT_CORE_NONCOPYABLE__

namespace Pot
{

class NonCopyable
{
	protected:
		NonCopyable() {}
	
	private:
		NonCopyable(const NonCopyable&);
		NonCopyable& operator=(const NonCopyable&);
};

}

#endif
