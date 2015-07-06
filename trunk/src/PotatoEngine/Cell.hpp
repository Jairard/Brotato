#ifndef __CELL__
#define __CELL__

#include "../Core/NonCopyable.hpp"
#include "Potato.hpp"

#include "Debug/Logger.hpp"

namespace Pot
{
	
namespace Debug
{
	class Renderer;
}

class Cell: NonCopyable
{
	friend class Potato;
	
	public:
		// TODO: find a way to not pass the potato manually
		// something like: potato->AddCell<T>()
		// or potato->InstantiateCell<T>()
		// or RenderCell::Create(potato, args, ...)
		Cell(Potato* potato): m_potato(potato)
		{}
		
		virtual ~Cell() {}
		
		virtual void update() = 0;
		
		Potato* sPotato(void)              { assert(m_potato != nullptr); return m_potato; }
		const Potato* sPotato(void) const  { assert(m_potato != nullptr); return m_potato; }
		
	private:
		void debugRender(Debug::Renderer& renderer) const { UNUSED(renderer); }
	//private
	/*
	public:
		template<typename... Args>
		void initialize(Args... args)
		{
			Debug::Logger::log(Debug::Logger::CWarning, "nope :(");
			VUNUSED(args);
		}
	//*/
		
	private:
		Potato* m_potato;
};

/*
#include <iostream>
template<typename... Args>
void initializeCell(Args... args)
{
	VUNUSED(args);
	std::cout << "nope :(" << std::endl;
}
//*/

}

#endif
