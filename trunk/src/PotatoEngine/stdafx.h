// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifndef __POT_STD_AFX__
#define __POT_STD_AFX__

#include <Core/compil.hpp>
#define NOMINMAX
#include <targetver.h>

#ifdef POT_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#endif

// C RunTime Header Files
#include <stdlib.h>
#include <memory.h>
// TODO: get rid of those files ?
#ifdef POT_PLATFORM_WINDOWS
#include <malloc.h>
#include <tchar.h>
#pragma warning(disable : 4091) // "'typedef ' : ignoré à gauche de '[...]' quand aucune variable n'est déclarée"
#pragma warning(disable : 4996) // "'GetVersionExA': a été déclaré déconseillé"
#endif

#ifdef POT_COMPILER_GCC
# define POT_FUNC __PRETTY_FUNCTION__
#else
# define POT_FUNC __FUNCTION__
#endif

#define POT_UNUSED(X)  ((void)(X))
#ifdef POT_COMPILER_GCC
struct TOOLS_VSINK { template<typename ...Args> TOOLS_VSINK(const Args& ... ) {} };
# define POT_VUNUSED(X) TOOLS_VSINK {X...}
# define POT_FUNUSED(X) X __attribute__((unused))
#else
# define POT_VUNUSED(X)
# define POT_FUNUSED(X) X
#endif

#if defined(POT_COMPILER_GCC)
# define POT_CONST_EXPR constexpr
# define POT_CONST_EXPR_SUPPORT
#elif defined(POT_COMPILER_MSC)
# if (_MSC_VER >= 1900)
#  define POT_CONST_EXPR constexpr
#  define POT_CONST_EXPR_SUPPORT
# else
#  define POT_CONST_EXPR
# endif
#else
# define POT_CONST_EXPR
#endif

#ifdef POT_CONST_EXPR_SUPPORT
# define POT_STATIC_IS(T1, T2)  ::Pot::Tools::is<T1, T2>()
#else
# define POT_STATIC_IS(T1, T2)  ::std::is_base_of<T2, T1>::value
#endif

// TODO: reference additional headers your program requires here
#endif
