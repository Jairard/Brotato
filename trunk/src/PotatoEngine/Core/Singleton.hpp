#ifndef __POT_CORE_SINGLETON__
#define __POT_CORE_SINGLETON__

#include <cstddef>
#include "../Debug/assert.hpp"

namespace Pot
{

template <typename T>
class Singleton
{
	public:
		static void instantiate()
		{
			ASSERT_DEBUG(!hasInstance());
			m_instance = new T();
		}

		static T& instance()
		{
			ASSERT_RELEASE(hasInstance());
			return *m_instance;
		}

		static T* instanceIFP()
		{
			return m_instance;
		}

		static void deleteInstance()
		{
			ASSERT_DEBUG(hasInstance());
			delete m_instance;
			m_instance = nullptr;
		}

		static bool hasInstance()
		{
			return m_instance != nullptr;
		}

	protected:
		Singleton()
		{}

		virtual ~Singleton()
		{}

	private:
		static T* m_instance;
};

template <typename T>
T* Singleton<T>::m_instance = nullptr;

}

#endif
