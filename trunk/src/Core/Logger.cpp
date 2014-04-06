#include <iostream>
#include <sstream>
#include <ctime>
#include "Logger.hpp"

const std::string Logger::Warning = "Warning";
const std::string Logger::Error = "Error";
const std::string Logger::Default = "Default";

const int Logger::BUFFER_SIZE = 4096;
std::list<std::string> Logger::m_enabledTags = std::list<std::string>();
const std::string Logger::m_vlogError = "An error occured while reading formatted data";
const std::string Logger::m_vlogBufferSizeError = Logger::m_vlogError + ": reallocated buffer had insufficient size";

void Logger::Log(const std::string& msg)
{
	Log(Default, msg);
}

void Logger::Log(const std::string& tag, const std::string& msg)
{
	Log(std::cout, tag, msg);
}

void Logger::Log(std::ostream& stream, const std::string& tag, const std::string& msg)
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
void Logger::Log(const char* fmt, ...)
{
	va_list list;
	
	va_start(list, fmt);
	int n = vLog(BUFFER_SIZE, fmt, list);
	va_end(list);
	
	// An error occured
	if (n < 0)
		Log(Error, m_vlogError);
	// The buffer was not big enough,
	// give it another try with adapted size
	else if (n >= BUFFER_SIZE )
	{
		const int newSize = n+1; 
		
		va_start(list, fmt);
		int n2 = vLog(newSize, fmt, list);
		va_end(list);
		
		// An error occured
		if (n2 < 0)
			Log(Error, m_vlogError);
		// Buffer still too small (this should not happen)
		else if(n2 >= newSize)
			Log(Error, m_vlogBufferSizeError);
	}
}

void Logger::Log(const char* tag, const char* fmt, ...)
{
	va_list list;
	
	va_start(list, fmt);
	int n = vLog(tag, BUFFER_SIZE, fmt, list);
	va_end(list);
	
	if (n < 0)
		Log(Error, m_vlogError);
	else if (n >= BUFFER_SIZE )
	{
		const int newSize = n+1; 
		
		va_start(list, fmt);
		int n2 = vLog(tag, newSize, fmt, list);
		va_end(list);
		
		if (n2 < 0)
			Log(Error, m_vlogError);
		else if(n2 >= newSize)
			Log(Error, m_vlogBufferSizeError);
	}
}

void Logger::Log(std::ostream& stream, const char* tag, const char* fmt, ...)
{
	va_list list;
	
	va_start(list, fmt);
	int n = vLog(stream, tag, BUFFER_SIZE, fmt, list);
	va_end(list);
	
	if (n < 0)
		Log(stream, Error, m_vlogError);
	else if (n >= BUFFER_SIZE )
	{
		const int newSize = n+1; 
		
		va_start(list, fmt);
		int n2 = vLog(tag, newSize, fmt, list);
		va_end(list);
		
		if (n2 < 0)
			Log(stream, Error, m_vlogError);
		else if(n2 >= newSize)
			Log(stream, Error, m_vlogBufferSizeError);
	}
}

int Logger::vLog(int bufferSize, const char* fmt, va_list list)
{
	return vLog(Default.c_str(), bufferSize, fmt, list);
}

int Logger::vLog(const char* tag, int bufferSize, const char* fmt, va_list list)
{
	return vLog(std::cout, tag, bufferSize, fmt, list);
}

int Logger::vLog(std::ostream& stream, const char* tag, int bufferSize, const char* fmt, va_list list)
{
	char* buffer = new char[bufferSize];
	
	int n = vsnprintf(buffer, bufferSize, fmt, list);
	// Everything went OK
	if (n >= 0 && n < bufferSize)
		Log(stream, std::string(tag), std::string(buffer));
	
	delete buffer;
	
	return n;
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
