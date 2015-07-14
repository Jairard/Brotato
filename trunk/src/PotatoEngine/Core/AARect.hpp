#ifndef __AARECT__
#define __AARECT__

#include "../../Core/Vector2.hpp"

namespace Pot
{

struct AARect
{
	float left, bottom, width, height;
	
	AARect():
		left(0.f),
		bottom(0.f),
		width(0.f),
		height(0.f)
	{}
	
	AARect(float rectLeft, float rectBottom, float rectWidth, float rectHeight):
		left(rectLeft),
		bottom(rectBottom),
		width(rectWidth),
		height(rectHeight)
	{}
	
	AARect(const Vector2f& position, const Vector2f& size):
		left(position.x),
		bottom(position.y),
		width(size.x),
		height(size.y)
	{}
};

}

#endif
