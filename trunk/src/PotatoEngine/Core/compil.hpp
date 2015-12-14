#ifndef __POT_CORE_COMPIL_HPP__
#define __POT_CORE_COMPIL_HPP__

// Platform
#ifdef __APPLE__
# define POT_PLATFORM_OSX
#elif defined(__WIN32__) || defined(_WIN32) || defined(__CYGWIN32__)
# define POT_PLATFORM_WINDOWS
#elif defined(__linux__) || defined(__linux) || defined(linux)
# define POT_PLATFORM_LINUX
#else
# define POT_PLATFORM_UNKNOWN
#pragma message("Unknown platform")
#endif

// Compiler
#if defined(_GNUC) || defined(__GNUC__)
# define POT_COMPILER_GCC
#elif defined(_MSC_VER)
# define POT_COMPILER_MSC
#else
#pragma message("Unknown compiler")
#endif

// Configuration
// TODO: name correctly and bind
#define SOME_DEBUG_CONSTANT

#define POT_RELEASE

#ifdef SOME_DEBUG_CONSTANT
# undef POT_RELEASE
# define POT_DEBUG
#endif

#if defined(POT_RELEASE) && defined(POT_DEBUG)
#error You can't define POT_DEBUG and POT_RELEASE at the same time
#endif

#endif
