#include <stdafx.h>
#include "Cell.hpp"

#include <iostream>
#include <Debug/Renderer.hpp>

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
	POT_UNUSED(renderer);
}

}

