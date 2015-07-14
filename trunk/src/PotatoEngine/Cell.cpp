#include "Cell.hpp"

#include <iostream>

namespace Pot
{

/*
template<typename... Args>
void initializeCell(Args... args)
{
	VUNUSED(args);
	std::cout << "nope :(" << std::endl;
}
//*/

void Cell::debugRender(Debug::Renderer& renderer) const
{
	UNUSED(renderer);
}

}

