#include "Demangler.hpp"

#include "../Core/Tools.hpp"
#include "Logger.hpp"

namespace Pot { namespace Debug
{
	Demangler::Demangler(const char* name, bool permissive):
		m_res(),
		m_success(false),
		m_permissive(permissive)
	{
		demangle(name);
	}

	template <>
	Demangler::Demangler(const std::type_info& type, bool permissive):
		m_res(),
		m_success(false),
		m_permissive(permissive)
	{
		demangle(type.name());
	}

	template <>
	Demangler::Demangler(const std::type_index& type, bool permissive):
		m_res(),
		m_success(false),
		m_permissive(permissive)
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

	bool Demangler::success() const
	{
		return m_success;
	}

	void Demangler::demangle(const char* name)
	{
		ASSERT_DEBUG(name != nullptr);

#ifdef _MSC_VER
        m_res.assign(name);
#else
		int status = 0;
		char* res = abi::__cxa_demangle(name, nullptr, nullptr, &status);
		m_success = (status == 0);

		switch (status)
		{
			case 0: // Success
				break;

			case -1:
				if (!m_permissive)
					ASSERT_DEBUG_MSG(false, "demangleName: a memory allocation failiure occurred");
				break;
			case -2:
				if (!m_permissive)
				{
					std::ostringstream oss;
					oss << "demangleName: "
						<< "'" << name << "'"
						<< " is not a valid name under the C++ ABI mangling rules";
					ASSERT_DEBUG_MSG(false, oss.str().c_str());
				}
				break;
			case -3:
				if (!m_permissive)
					ASSERT_DEBUG_MSG(false, "demangleName: one of the arguments is invalid");
				break;

			default:
				ASSERT_NOT_REACHED();
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
#endif
	}
}}

std::ostream& operator<<(std::ostream& stream, const Pot::Debug::Demangler& demangler)
{
	stream << demangler.str();
	return stream;
}

