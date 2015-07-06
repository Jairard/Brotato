#ifndef __POOL__
#define __POOL__

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <list>

template <typename T>
class Pool
{
	public:
		Pool(bool allowSafetyChecks = false, size_t capacity = c_defaultCapacity):
			m_allowSafetyChecks(allowSafetyChecks),
			m_capacity(capacity)
		{
			m_data = new T[m_capacity];
			
			for (std::size_t i = 0; i < m_capacity; ++i)
				m_avaibleChunks.push_back(i);
		}
		
		~Pool()
		{
			delete[] m_data;
		}
		
		T* create()
		{
			assert(!isFull());
			
			T* chunk = &m_data[m_avaibleChunks.front()];
			m_avaibleChunks.pop_front();
			
			return chunk;
		}
		
		void destroy(T* chunk)
		{
			destroy(chunk - m_data);
		}
		
		bool isFull(void) const
		{
			return m_avaibleChunks.empty();
		}
		
		size_t capacity() const
		{
			return m_capacity;
		}
		
		size_t availableChunkCount() const
		{
			return m_avaibleChunks.size();
		}
		
		size_t usedChunkCount() const
		{
			return capacity() - availableChunkCount();
		}
		
	private:
		void destroy(size_t i)
		{
			assert(i >= 0);
			assert(i < m_capacity);
			
			if (m_allowSafetyChecks)
				assert(!isAvailable(i));
			
			m_avaibleChunks.push_front(i);
		}
		
		bool isAvailable(size_t i)
		{
			for (std::list<size_t>::iterator it = m_avaibleChunks.begin(); it != m_avaibleChunks.end(); ++it)
				if (*it == i)
					return true;
			
			return false;
		}
		
	private:
		static const size_t c_defaultCapacity = 256;
		
		T* m_data;
		bool m_allowSafetyChecks;
		std::list<size_t> m_avaibleChunks;
		std::size_t m_capacity;
};
#endif
