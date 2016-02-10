#include <stdafx.h>
#include "BuildConfig.hpp"

namespace Pot { namespace BuildConfig
{
// Platform
#if defined(POT_PLATFORM_AIX)
	const Platform::Type os = Platform::AIX;
	const std::string osAsString = "AIX";
#elif defined(POT_PLATFORM_BSD)
	const Platform::Type os = Platform::BSD;
	const std::string osAsString = "BSD";
#elif defined(POT_PLATFORM_HP_UX)
	const Platform::Type os = Platform::HP_UX;
	const std::string osAsString = "HP_UX";
#elif defined(POT_PLATFORM_LINUX)
	const Platform::Type os = Platform::Linux;
	const std::string osAsString = "OSX";
#elif defined(POT_PLATFORM_OSX)
	const Platform::Type os = Platform::OSX;
	const std::string osAsString = "OSX";
#elif defined(POT_PLATFORM_SOLARIS)
	const Platform::Type os = Platform::Solaris;
	const std::string osAsString = "Solaris";
#elif defined(POT_PLATFORM_WINDOWS)
	const Platform::Type os = Platform::Windows;
	const std::string osAsString = "Windows";
#else
	const Platform::Type os = Platform::Unknow;
	const std::string osAsString = "Unknow";
#endif

// Unix
#ifdef POT_PLATFORM_IS_UNIX
	const bool isUnix = true;
#else
	const bool isUnix = false;
#endif

// Compiler
#if defined(POT_COMPILER_GCC)
	const Compiler::Type compiler = Compiler::GCC;
	const std::string compilerAsString = "GCC";
#elif defined(POT_COMPILER_MSC)
	const Compiler::Type compiler = Compiler::MSC;
	const std::string compilerAsString = "MSC";
#elif defined(POT_COMPILER_MINGW)
	const Compiler::Type compiler = Compiler::MinGW;
	const std::string compilerAsString = "MinGW";
#else
	const Compiler::Type compiler = Compiler::Unknown;
	const std::string compilerAsString = "Unknown";
#endif

// Build type
#if defined(POT_DEBUG)
	const Build::Type build = Build::Debug;
	const std::string buildAsString = "Debug";
#elif defined(POT_RELEASE)
	const Build::Type build = Build::Release;
	const std::string buildAsString = "Release";
#else
	const Build::Type build = Build::Other;
	const std::string buildAsString = "Other";
#endif

	const std::string buildConfigAsString = "BuildConfig[Platform: " + osAsString + \
	                                        ", Compiler: " + compilerAsString + \
	                                        ", " + buildAsString + "]";
}}
