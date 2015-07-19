#ifndef __NONCOPYABLE__
#define __NONCOPYABLE__

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
