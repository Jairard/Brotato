#ifndef __POT_DEBUG_LOGGER__
#define __POT_DEBUG_LOGGER__

#include <list>
#include <stdarg.h>
#include <string>
#include <Core/NonInstantiable.hpp>

namespace Pot 
{
namespace Debug
{
	class Logger : public NonInstantiable
	{
		/* Methods */
		public:
			static void setDefaultStream(std::ostream& stream);
			/* C++-like logs */
			static void log(const std::string& msg);
			static void log(const std::string& tag, const std::string& msg);
			static void log(std::ostream& stream, const std::string& tag, const std::string& msg);
			/* C-like logs */
			static void log(const char* fmt, ...);
			static void log(const char* tag, const char* fmt, ...);
			static void log(std::ostream& stream, const char* tag, const char* fmt, ...);
			/* Tags methods */
			static void initTags(void);
			static void enableTag(const std::string& tag);
			static void disableTag(const std::string& tag);
			std::list<std::string>& tags(void);
			
		protected:
			/* For C-like logs */
			static void vLog(const char* fmt, va_list list);
			static void vLog(const char* tag, const char* fmt, va_list list);
			static void vLog(std::ostream& stream, const char* tag, const char* fmt, va_list list);
			static void logVariadicError(std::ostream& stream);
			/* Tags methods */
			static bool isTagEnabled(const std::string& tag);
			/* Format methods */
			static std::ostream& outputTime(std::ostream& stream, tm* time);
			static std::ostream& outputTag(std::ostream& stream, const std::string& tag);
			
		private:
			static tm* currentTime(void);
            static std::ostream& logImpl(std::ostream& stream, const char* msg);
		
		/* Members */
		public:
			static const char* CInfo;
			static const char* CWarning;
			static const char* CError;
			static const char* CDefault;
			static const char* CAssert;
			static const std::string Info;
			static const std::string Warning;
			static const std::string Error;
			static const std::string Default;
			static const std::string Assert;
			
		protected:
            static const size_t c_bufferSize;
            static const std::string c_vlogError;
			static std::list<std::string> m_enabledTags;
			static std::ostream* m_defaultStream;
	};
}
}

#endif
