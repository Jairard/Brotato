#include "../stdafx.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <ctime>
#ifdef POT_COMPILER_MSC // POT_PLATFORM_WINDOWS ?
# include <debugapi.h>
#endif
#include "Logger.hpp"
#include "assert.hpp"

namespace Pot
{
namespace Debug
{

const char* Logger::CInfo = "Info";
const char* Logger::CWarning = "Warning";
const char* Logger::CError = "Error";
const char* Logger::CDefault = "Default";
const char* Logger::CAssert = "Assert";
const std::string Logger::Info = Logger::CInfo;
const std::string Logger::Warning = Logger::CWarning;
const std::string Logger::Error = Logger::CError;
const std::string Logger::Default = Logger::CDefault;
const std::string Logger::Assert = Logger::CAssert;

const size_t Logger::c_bufferSize = 8192;
const std::string Logger::c_vlogError = "An error occured while reading formatted data";
std::list<std::string> Logger::m_enabledTags = std::list<std::string>();
std::ostream* Logger::m_defaultStream = &std::cout;

void Logger::setDefaultStream(std::ostream& stream)
{
	m_defaultStream = &stream;
}

void Logger::log(const std::string& msg)
{
	log(Default, msg);
}

void Logger::log(const std::string& tag, const std::string& msg)
{
	log(*m_defaultStream, tag, msg);
}

void Logger::log(std::ostream& stream, const std::string& tag, const std::string& msg)
{
	if (m_enabledTags.empty())
		initTags();
	
	if (!isTagEnabled(tag))
		return;
	
    // Using returned stream adds a '1' at the end
    std::stringstream str;
	outputTime(str, currentTime());
	outputTag(str, tag);
	str << msg << std::endl;

    logImpl(stream, str.str().c_str());
}

// Can't factorise code with Log(std::ostream& stream, const char* tag, const char* fmt, ...)
// because of variadic arg (can't call Log(std::cout, tag, fmt, ...) )
void Logger::log(const char* fmt, ...)
{
	va_list list;
	
	va_start(list, fmt);
	vLog(fmt, list);
	va_end(list);
}

void Logger::log(const char* tag, const char* fmt, ...)
{
	va_list list;
	
	va_start(list, fmt);
	vLog(tag, fmt, list);
	va_end(list);
}

void Logger::log(std::ostream& stream, const char* tag, const char* fmt, ...)
{
	va_list list;
	
	va_start(list, fmt);
	vLog(stream, tag, fmt, list);
	va_end(list);
}

void Logger::vLog(const char* fmt, va_list list)
{
	vLog(Default.c_str(), fmt, list);
}

void Logger::vLog(const char* tag, const char* fmt, va_list list)
{
	vLog(*m_defaultStream, tag, fmt, list);
}

void Logger::vLog(std::ostream& stream, const char* tag, const char* fmt, va_list list)
{
	if (!isTagEnabled(tag))
		return;
	
    char buffer[c_bufferSize];
	int n = vsnprintf(buffer, c_bufferSize, fmt, list);
	// No error occured (but the buffer was potentially not big enough)
	if (n >= 0)
	{
		if (static_cast<size_t>(n) >= c_bufferSize)
		{
			logVariadicError(stream);
			buffer[c_bufferSize-1] = '\0';
		}
		log(stream, std::string(tag), std::string(buffer));
	}
}

void Logger::logVariadicError(std::ostream& stream)
{
	std::stringstream str;
	str << c_vlogError << " (buffer size: " << c_bufferSize << ")";
	log(stream, Error, str.str());
}

bool Logger::isTagEnabled(const std::string& tag)
{
	std::list<std::string>::const_iterator it;

	for (it=m_enabledTags.begin(); it!=m_enabledTags.end(); it++)
		if (*it == tag)
			return true;

	return false;
}

void Logger::initTags()
{
	m_enabledTags.clear();
	m_enabledTags.push_back(Error);
	m_enabledTags.push_back(Warning);
	m_enabledTags.push_back(Default);
}

void Logger::enableTag(const std::string& tag)
{
	if (m_enabledTags.empty())
		initTags();
	
	m_enabledTags.push_back(tag);
}

void Logger::disableTag(const std::string& tag)
{
	std::list<std::string>::iterator it;

	for (it=m_enabledTags.begin(); it!=m_enabledTags.end(); it++)
		if (*it == tag)
			it = m_enabledTags.erase(it);
}

std::list<std::string>& Logger::tags()
{
	return m_enabledTags;
}

std::ostream& Logger::outputTag(std::ostream& stream, const std::string& tag)
{
	return stream << " - " << tag << " - ";
}

std::ostream& Logger::outputTime(std::ostream& stream, tm* time)
{
	char fill = stream.fill();
	std::streamsize width = stream.width();
	
	stream.fill('0');
	stream << "[";
	stream.width(2);
	stream << time->tm_mday << "/";
	stream.width(2);
	stream << time->tm_mon + 1 << "/";
	stream.width(2);
	stream << time->tm_year + 1900 << " ";
	
	stream.width(2);
	stream << time->tm_hour << ":";
	stream.width(2);
	stream << time->tm_min << ":";
	stream.width(2);
	stream << time->tm_sec;
	stream << "]";
	
	stream.fill(fill);
	stream.width(width);
	
	return stream;
}

tm* Logger::currentTime()
{
	time_t now = time(0);
	return localtime(&now);
}

std::ostream& Logger::logImpl(std::ostream& stream, const char* str)
{
	ASSERT_RELEASE(str != nullptr);

#ifdef POT_COMPILER_MSC // POT_PLATFORM_WINDOWS ?
	OutputDebugStringA(str);
#else
	stream << str;
#endif

	return stream;
}

}
}
