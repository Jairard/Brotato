#ifndef __POT_CORE_TOOLS__
#define __POT_CORE_TOOLS__

#include <typeinfo>
#include <type_traits>
#include <string>
#include <sstream>
#include <cxxabi.h>
#include "../Debug/assert.hpp"
#include "NonInstantiable.hpp"

#define UNUSED(x)		((void)(x))
struct TOOLS_VSINK { template<typename ...Args> TOOLS_VSINK(Args const & ... ) {} };
#define VUNUSED(x)		TOOLS_VSINK {x...}
#define FUNUSED(x)		x __attribute__((unused))

namespace Pot
{

class Tools: public NonInstantiable
{
	public:
		template <typename T, typename U>
		static bool is(const U* ptr)
		{
			return ptr == nullptr || isStrictly<T>(ptr) || as<T>(ptr) != nullptr;
		}

		template <typename T, typename U>
		static bool is(U* ptr)
		{
			return ptr == nullptr || isStrictly<T>(ptr) || as<T>(ptr) != nullptr;
		}

		template <typename T, typename U>
		static constexpr bool is()
		{
			// is_base_of<Base, Derived>
			return std::is_base_of<U, T>();
		}

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
		static constexpr bool isStrictly()
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

		static std::string demangledName(const char* name)
		{
			int status = 0;
			char* res = abi::__cxa_demangle(name, nullptr, nullptr, &status);

			switch (status)
			{
				case -1:
					ASSERT_DEBUG_MSG(false, "demangleName: a memory allocation failiure occurred");
					break;
				case -2:
					{
						std::ostringstream oss;
						oss << "demangleName: "
							<< "'" << name << "'"
							<< " is not a valid name under the C++ ABI mangling rules";
						ASSERT_DEBUG_MSG(false, oss.str().c_str());
					}
					break;
				case -3:
					ASSERT_DEBUG_MSG(false, "demangleName: one of the arguments is invalid");
					break;
				default:
					break;
			}

			if (status != 0)
				return std::string(name);

			std::string resString(res);
			free(res);
			return resString;
		}
};

}

#endif
