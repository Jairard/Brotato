#include "Demangler.hpp"

#include "../Core/Tools.hpp"
#include "Logger.hpp"

namespace Pot { namespace Debug
{
	Demangler::Demangler(const char* name)
	{
		demangle(name);
	}

	template <>
	Demangler::Demangler(const std::type_info& type)
	{
		demangle(type.name());
	}

	template <>
	Demangler::Demangler(const std::type_index& type)
	{
		demangle(type.name());
	}

	const char* Demangler::operator()() const
	{
		return c_str();
	}

	const std::string& Demangler::str() const
	{
		return m_res;
	}

	const char* Demangler::c_str() const
	{
		return m_res.c_str();
	}

	void Demangler::demangle(const char* name)
	{
		ASSERT_DEBUG(name != nullptr);

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
			m_res.assign(name);
		else
		{
			m_res.assign(res);
			if (m_res.empty()) // There was nothing to demangle
				m_res.assign(name);
			free(res);
		}
	}
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::Demangler& demangler)
{
	stream << demangler.str();
	return stream;
}

