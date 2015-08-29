#ifndef __STAINABLE__
#define __STAINABLE__

namespace Pot
{

template <typename T>
class Stainable
{
	public:
		Stainable():
			m_object(),
			m_isRotten(false)
		{}

		Stainable(const Stainable<T>& other):
			m_object(other.const_object()),
			m_isRotten(true)
		{}

		void soil(void)                   { m_isRotten = true; }
		void wash(void)                   { m_isRotten = false; }
		bool isRotten() const             { return m_isRotten; }
		const T& const_object(void) const { return m_object; }
		T& object(void)
		{
			m_isRotten = true;
			return m_object;
		}

		Stainable<T>& operator=(const Stainable<T>& other)
		{
			m_object = other.m_object;
			m_isRotten = true;
			return *this;
		}

		Stainable<T>& operator=(const T& other)
		{
			m_object = other;
			m_isRotten = true;
			return *this;
		}

		bool operator==(const Stainable<T>& other)
		{
			return const_object() == other.const_object();
		}

		bool operator==(const T& other)
		{
			return const_object() == other;
		}

	private:
		T m_object;
		bool m_isRotten;
};

}

#endif 
