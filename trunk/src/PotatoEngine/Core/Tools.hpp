#ifndef __POT_CORE_TOOLS__
#define __POT_CORE_TOOLS__

#include <typeinfo>
#include <type_traits>
#include <string>
#include <sstream>
#include "../stdafx.h"
#include "../Debug/assert.hpp"
#include "compil.hpp"
#include "NonInstantiable.hpp"

#ifdef POT_COMPILER_GCC
#include <cxxabi.h>
#endif

namespace Pot
{

class Tools: public NonInstantiable
{
	public:
		// Useless ?
		template <typename T, typename U>
		static bool is(const U* ptr)
		{
			POT_UNUSED(ptr);
			return is<T, U>();
		}

		template <typename T, typename U>
		static bool is(U* ptr)
		{
			POT_UNUSED(ptr);
			return is<T, U>();
		}

		template <typename T, typename U>
		static POT_CONST_EXPR bool is()
		{
			// is_base_of<Base, Derived>
			return std::is_base_of<U, T>();
		}

		/*
		A* b = new B();
		A* c = new C();
		typeid(b) == typeid(c) ?
		*/
		template <typename T, typename U>
		static bool isStrictly(U*)
		{
			return typeid(U) == typeid(T);
		}

		template <typename T, typename U>
		static bool isStrictly(const U*)
		{
			return typeid(U) == typeid(T);
		}

		template <typename T, typename U>
		static POT_CONST_EXPR bool isStrictly()
		{
			return typeid(U) == typeid(T);
		}

		template <typename T, typename U>
		static T* as(U* ptr)
		{
			ASSERT_DEBUG_MSG(ptr == nullptr || dynamic_cast<T*>(ptr) != nullptr, "Invalid cast");
			return static_cast<T*>(ptr);
		}

		static const char* bool2str(bool expr)
		{
			static const char* str[2] = {"false", "true"};
			return str[expr];
		}
};

}

#endif
