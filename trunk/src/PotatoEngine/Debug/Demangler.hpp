#ifndef __POT_DEBUG_DEMANGLER__
#define __POT_DEBUG_DEMANGLER__

#include <typeinfo>
#include <typeindex>
#include <string>
#include <ostream>
#include "Logger.hpp"

namespace Pot { namespace Debug
{
	class Demangler
	{
		public:
			Demangler(const char* name);
			//Demangler(const std::type_index& type);
			template <typename T>
			Demangler(const T& object);
			//template <>
			//Demangler(const std::type_index& type);

			const char* operator()() const;
			const std::string& str() const;
			const char* c_str() const;

		private:
			void demangle(const char*);

		private:
			std::string m_res;
	};

	template <typename T>
	Demangler::Demangler(const T& object)
	{
		demangle(typeid(object).name());
	}

	template <>
	Demangler::Demangler(const std::type_info& type);
	template <>
	Demangler::Demangler(const std::type_index& type);
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::Demangler& demangler);

#endif
