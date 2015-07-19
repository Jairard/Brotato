#ifndef __DEBUG_CALLSTACK__
#define __DEBUG_CALLSTACK__

#include <execinfo.h>
#include <list>
#include "../PotatoEngine/Core/NonInstantiable.hpp"

namespace Debug
{
#ifndef DEBUG
# define FUNC_ENTRY        Debug::CallStack::pushFrame(__FILE__, __LINE__, __func__)
# define LOG_STACK         Debug::CallStack::log(__FILE__, __LINE__)
# define FUNC_EXIT         Debug::CallStack::popFrame()
	
	class CallStack: public Pot::NonInstantiable
	{
		public:
			static void pushFrame(const char* file, int line, const char* function);
			static void popFrame(void);
			static void log(const char* file, int line);
			static void logBacktrace(void);
			static const std::string& tag(void)  { return s_tag; }
			
		private:
			typedef struct SStackFrame
			{
				std::string file;
				std::string function;
				const int line;
				
				SStackFrame(const char* file, int line, const char* function):
					file(file),
					function(function),
					line(line)
				{}
				
				void log(std::ostream& stream);
			} SStackFrame;
			
			static std::list<SStackFrame> s_frames;
			static const std::string s_tag;
			static const std::string s_filePrefix;
			static const int s_maxFrameCount;
	};
#else
# define FUNC_ENTRY
# define LOG_STACK
# define FUNC_EXIT
#endif
}

#endif
