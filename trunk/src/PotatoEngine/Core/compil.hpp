#ifndef __POT_CORE_COMPIL_HPP__
#define __POT_CORE_COMPIL_HPP__

// TODO:
// - unify compilation error (#pragma message() vs #error)
// - improve compiler detection

//////////////
// Platform //
//////////////
#if defined(__APPLE__) || defined(__MACH__)
# define POT_PLATFORM_OSX
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || \
      defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__) || \
      defined(WINNT) || defined(__WINNT) || defined(__WINNT__)
# define POT_PLATFORM_WINDOWS
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux)
# define POT_PLATFORM_LINUX
•elif defined(_AIX)
# define POT_PLATFORM_AIX
#elif defined(__DragonFly__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#d efine POT_PLATFORM_BSD
# if defined(__DragonFly__)
#  define POT_PLATFORM_DRAGONFLY_BSD
# elif defined(__FreeBSD__)
#  define POT_PLATFORM_FREEBSD
# elif defined(__NetBSD__)
#  define POT_PLATFORM_NETBSD
# elif defined(__OpenBSD__)
#  define POT_PLATFORM_OPENBSD
# else
#  error "Unknown BSD platform"
# endif
#elif defined(hpux) || defined(__hpux)
# define POT_PLATFORM_HP_UX
#elif defined(sun) || defined(__sun) || defined(__sun__) || defined(__SunOS) || defined(__svr4__) || defined(__SVR4)
# define POT_PLATFORM_SOLARIS
#else
# define POT_PLATFORM_UNKNOWN
#pragma message("Unknown platform")
#endif

// Unix (OSX doesn't define any unix macro but is still a unix os
#if defined(unix) || defined(__unix) || defined(__unix__) || defined(POT_PLATFORM_OSX)
#define POT_PLATFORM_IS_UNIX
#endif

//////////////
// Compiler //
//////////////
#if defined(_GNUC) || defined(__GNUC__)
# define POT_COMPILER_GCC
#elif defined(_MSC_VER)
# define POT_COMPILER_MSC
#elif defined(__MINGW32__) || defined(__MINGW64__)
# define POT_COMPILER_MINGW
#else
#pragma message("Unknown compiler")
#endif

////////////////////////
// Standard libraries //
////////////////////////
// Posix support and version
#ifdef POT_PLATFORM_IS_UNIX
# include <unistd.h>
# ifdef _POSIX_VERSION
#  define POT_POSIX_SUPPORT
#  define POT_POSIX_VERSION _POSIX_VERSION
# endif
#endif

// Cygwin
#if defined(__CYGWIN__) || defined(__CYGWIN32__)
# define POT_CYGWIN
#endif

// TODO: endianness ?

///////////////////
// Configuration //
///////////////////

#ifndef POT_DEBUG
# define POT_RELEASE
#endif

#if defined(POT_RELEASE) && defined(POT_DEBUG)
#error You can't define POT_RELEASE and POT_DEBUG at the same time
#elif !defined(POT_RELEASE) && !defined(POT_DEBUG)
#error You must define either POT_RELEASE or POT_DEBUG
#endif

#endif
