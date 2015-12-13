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
			Demangler(const char* name, bool permissive = false);
			template <typename T>
			Demangler(const T& object, bool permissive = false);

			const char* operator()() const;
			const std::string& str() const;
			const char* c_str() const;

			bool success() const;

		private:
			void demangle(const char*);

		private:
			std::string m_res;
			bool m_success;
			bool m_permissive;
	};

	template <typename T>
	Demangler::Demangler(const T& object, bool permissive):
		m_res(),
		m_success(false),
		m_permissive(permissive)
	{
		demangle(typeid(object).name());
	}

	template <>
	Demangler::Demangler(const std::type_info& type, bool permissive);
	template <>
	Demangler::Demangler(const std::type_index& type, bool permissive);
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::Demangler& demangler);

#endif
