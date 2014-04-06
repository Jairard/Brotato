#ifndef __CORE_LOGGER__
#define __CORE_LOGGER__

#include <list>
#include <string>
#include <stdarg.h>
#include "NonInstantiable.hpp"

class Logger : public NonInstantiable
{
	/* Methods */
	public:		
		/* C++-like logs */
		static void Log(const std::string& msg);
		static void Log(const std::string& tag, const std::string& msg);
		static void Log(std::ostream& stream, const std::string& tag, const std::string& msg);
		/* C-like logs */
		static void Log(const char* fmt, ...);
		static void Log(const char* tag, const char* fmt, ...);
		static void Log(std::ostream& stream, const char* tag, const char* fmt, ...);
		/* Tags methods */
		static void initTags(void);
		static void enableTag(const std::string& tag);
		static void disableTag(const std::string& tag);
		std::list<std::string>& tags(void);
		
	protected:
		/* For C-like logs */
		static int vLog(int bufferSize, const char* fmt, va_list list);
		static int vLog(const char* tag, int bufferSize, const char* fmt, va_list list);
		static int vLog(std::ostream& stream, const char* tag, int bufferSize, const char* fmt, va_list list);
		/* Tags methods */
		static bool isTagEnabled(const std::string& tag);
		/* Format methods */
		static std::ostream& outputTime(std::ostream& stream, tm* time);
		static std::ostream& outputTag(std::ostream& stream, const std::string& tag);
		
	private:
		static tm* currentTime(void); 
	
	/* Members */
	public:
		static const std::string Warning;
		static const std::string Error;
		static const std::string Default;
		
	protected:
		static const int BUFFER_SIZE;
		static std::list<std::string> m_enabledTags;
		static const std::string m_vlogError;
		static const std::string m_vlogBufferSizeError;
};

#endif
