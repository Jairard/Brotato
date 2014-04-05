#ifndef __CORE_SINGLETON__
#define __CORE_SINGLETON__

template <typename T>
class Singleton
{
    public:
        static T* instance(void)
        {
            if (!m_instance)
                m_instance = new T();
            return m_instance;
        }
        
        static void deleteInstance(void)
        {
            if (m_instance)
            {
                delete m_instance;
                m_instance = 0;
            }
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
T* Singleton<T>::m_instance = 0;

#endif
