#ifndef __SINGLETON__
#define __SINGLETON__

namespace Pot
{

template <typename T>
class Singleton
{
	public:
		static T* instance()
		{
			if (!hasInstance())
				m_instance = new T();
			return m_instance;
		}

		static void deleteInstance()
		{
			if (hasInstance())
			{
				delete m_instance;
				m_instance = nullptr;
			}
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
T* Singleton<T>::m_instance = nulltptr;

}

#endif
