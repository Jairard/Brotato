#ifndef __CORE_TOOLS__
#define __CORE_TOOLS__

#include <typeinfo>
#include "NonInstantiable.hpp"

#define UNUSED(x)		((void)(x))
struct TOOLS_VSINK { template<typename ...Args> TOOLS_VSINK(Args const & ... ) {} };
#define VUNUSED(x)		TOOLS_VSINK {x...}

class Tools: public NonInstantiable
{
	public:
		template <typename T, typename U>
		static bool is(const U* data)
		{
			// Does not work for derived types
			if (typeid(U) == typeid(T))
				return true;
			
			return as<T>(data) != 0;
		}
		template <typename T, typename U>
		static bool is(U* data)
		{
			// Does not work for derived types
			if (typeid(U) == typeid(T))
				return true;
			
			return as<T>(data) != 0;
		}
		
		template <typename T, typename U>
		static T* as(U* data)
		{
			return dynamic_cast<T*>(data);
		}
};

#endif
