#ifndef __AARECT__
#define __AARECT__

#include "Vector2.hpp"

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
	
	AARect(const AARect& other):
		left(other.left),
		bottom(other.bottom),
		width(other.width),
		height(other.height)
	{}
	
	AARect(float rectLeft, float rectBottom, float rectWidth, float rectHeight):
		left(rectLeft),
		bottom(rectBottom),
		width(rectWidth),
		height(rectHeight)
	{}
	
	AARect(const Vector2f& center, const Vector2f& size):
		left(center.x - size.x / 2.f),
		bottom(center.y - size.y / 2.f),
		width(size.x),
		height(size.y)
	{}
	
	bool operator==(const AARect& other)
	{
		return left   == other.left   &&
		       bottom == other.bottom &&
		       width  == other.width  &&
		       height == other.height;
	}
	
	AARect& operator=(const AARect& other)
	{
		left = other.left;
		bottom = other.bottom;
		width = other.width;
		height = other.height;
		
		return *this;
	}
};

}

#endif
