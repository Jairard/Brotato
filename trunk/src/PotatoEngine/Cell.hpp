#ifndef __CELL__
#define __CELL__

#include "Core/NonCopyable.hpp"
#include "Core/ClassHelpers.hpp"
#include "Debug/Logger.hpp"
#include "Potato.hpp"

namespace Pot
{
	
namespace Debug
{
	class Renderer;
}

class Cell: public NonCopyable
{
	friend class Potato;
	
	public:
		// TODO: find a way to not pass the potato manually
		// something like: potato->AddCell<T>()
		// or potato->InstantiateCell<T>()
		// or RenderCell::Create(potato, args, ...)
		Cell(Potato* potato): m_potato(potato)
		{}
		
		IMPL_VIRTUAL_DESTRUCTOR(Cell);
		
		virtual void update() = 0;
		
		SAFE_ACCESSOR_WITH_NAME(Potato*, potato, sPotato);
		SAFE_CONST_ACCESSOR_WITH_NAME(Potato*, potato, sPotato);
		
	protected:
		virtual void debugRender(Debug::Renderer& renderer) const;
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
