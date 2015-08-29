#ifndef __POT_CORE_COMPILFLAGS_HPP__
#define __POT_CORE_COMPILFLAGS_HPP__

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
