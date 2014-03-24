#ifndef __SINGLETON__
#define __SINGLETON__

class Singleton
{
    public:
        static Singleton* instance(void)
        {
            if (!m_instance)
                m_instance = new Singleton();
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
    
    private:
        static Singleton* m_instance;
        
        Singleton()
        {}
        
        ~Singleton()
        {}
};

Singleton* Singleton::m_instance = 0;

#endif
