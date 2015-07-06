#include <sstream>
#include "../Core/Logger.hpp"
#include "CallStack.hpp"

namespace Debug
{
#ifndef DEBUG
	std::list<CallStack::SStackFrame> CallStack::s_frames = std::list<CallStack::SStackFrame>();
	const std::string CallStack::s_tag = "callstack";
	const std::string CallStack::s_filePrefix = "../src/";
	const int CallStack::s_maxFrameCount = 100;
	
	void CallStack::pushFrame(const char* file, int line, const char* function)
	{
		s_frames.push_back(CallStack::SStackFrame(file, line - 2, function));
	}
	
	void CallStack::popFrame()
	{
		if (s_frames.size() < 1)
			Logger::log(Logger::Error.c_str(), "%s - Trying to remove a frame but the stack is empty", s_tag.c_str());
		else
			s_frames.erase(--s_frames.end());
	}
	
	void CallStack::log(const char* file, int line)
	{		
		std::string log = "";
		
		if (s_frames.size() < 1)
			log = "<empty stack>";
		else
		{
			std::stringstream stream;
			std::list<CallStack::SStackFrame>::iterator it;
			
			stream << std::endl;
		
			for (it=s_frames.begin(); it!=s_frames.end(); it++)
			{
				it->log(stream);
				stream << std::endl;
			}
			
			SStackFrame logFrame(file, line, __func__);
			logFrame.log(stream);
			
			log = stream.str();
		}
		
		Logger::log(s_tag, log);
	}
	
	void CallStack::logBacktrace()
	{
		std::stringstream stream;
		void** buffer = new void*[s_maxFrameCount];
		
		int frameCount = backtrace(buffer, s_maxFrameCount);
		stream << frameCount << " frame(s):";
		
		char** symbols = backtrace_symbols(buffer, frameCount);
		if (symbols == 0)
		{
			stream << "<Invalid symbols>";
			Logger::log(Logger::Error, stream.str());
			delete buffer;
			return;
		}
		
		for (int i=0; i<frameCount; i++)
			stream << std::endl << symbols[i];
		
		Logger::log(s_tag, stream.str());
		
		delete buffer;
		delete symbols;
	}
	
	void CallStack::SStackFrame::log(std::ostream& stream)
	{
		stream << file.erase(0, s_filePrefix.size()) << ":" << line << ": " << function;
	}

#endif
}

