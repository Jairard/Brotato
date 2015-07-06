#ifndef __NONCOPYABLE__
#define __NONCOPYABLE__

class NonCopyable
{
	protected:
		NonCopyable() {}
	
	private:
		NonCopyable(const NonCopyable&);
		NonCopyable& operator=(const NonCopyable&);
};

#endif
