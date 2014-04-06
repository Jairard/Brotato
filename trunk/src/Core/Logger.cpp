#include <iostream>
#include <sstream>
#include <ctime>
#include "Logger.hpp"

const std::string Logger::Warning = "Warning";
const std::string Logger::Error = "Error";
const std::string Logger::Default = "Default";

int Logger::m_bufferSize = 4096;
std::list<std::string> Logger::m_enabledTags = std::list<std::string>();
const std::string Logger::m_vlogError = "An error occured while reading formatted data";
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
	outputTime(stream, currentTime());
	outputTag(stream, tag);
	stream << msg << std::endl;
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

void Logger::setBufferSize(unsigned int size)
{
	m_bufferSize = (int)size;
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
	
	char* buffer = new char[m_bufferSize];
	
	int n = vsnprintf(buffer, m_bufferSize, fmt, list);
	// No error occured (but the buffer was potentially not big enough)
	if (n >= 0)
	{
		if (n >= m_bufferSize)
		{
			logVariadicError(stream);
			buffer[m_bufferSize-1] = '\0';
		}
		log(stream, std::string(tag), std::string(buffer));
	}
	
	delete buffer;
}

void Logger::logVariadicError(std::ostream& stream)
{
	std::stringstream str;
	str << m_vlogError << " (current buffer size: " << m_bufferSize << ")";
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
	int width = stream.width();
	
	stream.fill('0');
	stream << "[";
	stream.width(2);
	stream << time->tm_hour << ":";
	stream.width(2);
	stream << time->tm_min << ":";
	stream.width(2);
	stream << time->tm_sec << " ";
	
	stream.width(2);
	stream << time->tm_mday << "/";
	stream.width(2);
	stream << time->tm_mon + 1 << "/";
	stream.width(2);
	stream << time->tm_year + 1900;
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
