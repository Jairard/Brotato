#ifndef __POT_BUILD_CONFIG__
#define __POT_BUILD_CONFIG__

#include <string>
#include <Core/compil.hpp>

namespace Pot { namespace BuildConfig
{
	// TODO: endianness ?
	namespace Platform
	{
		enum Type
		{
			AIX,
			BSD,
			HP_UX,
			Linux,
			OSX,
			Solaris,
			Windows,

			Unknown
		};
	}

	namespace Compiler
	{
		enum Type
		{
			GCC,
			MSC,
			MinGW,

			Unknown
		};
	}

	namespace Build
	{
		enum Type
		{
			Release,
			Debug,

			Other
		};
	}

	extern const Platform::Type os;
	extern const bool isUnix;
	extern const Compiler::Type compiler;
	extern const Build::Type build;

	extern const std::string osAsString;
	extern const std::string compilerAsString;
	extern const std::string buildAsString;

	extern const std::string buildConfigAsString;
}}

#endif
