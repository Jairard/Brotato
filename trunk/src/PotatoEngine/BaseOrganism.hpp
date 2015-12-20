#ifndef __POT_BASE_ORGANISM__
#define __POT_BASE_ORGANISM__

#include "Core/compil.hpp"
#ifdef POT_DEBUG
# include "DNACollector.hpp"
# include "Debug/Callstack.hpp"
#endif

namespace Pot
{
	class BaseOrganism
	{
		template <typename T> friend class Pool;
#ifdef POT_DEBUG
		friend class DNACollector;
#endif

	protected:
		BaseOrganism();
		virtual ~BaseOrganism();

	private:
		void shutdown() const;

#ifdef POT_DEBUG
	private:
		static const size_t c_framesToSkip;
		Debug::Callstack m_callstack;
#endif
	};
}

#endif
