#ifndef __RECT__
#define __RECT__

#include "../../Core/Vector2.hpp"

namespace Pot
{

struct Rect
{
	static const unsigned int c_pointCount = 4;
	Vector2f points[4];
	
	Rect()
	{
		for (unsigned int i = 0; i < c_pointCount; ++i)
			points[i] = Vector2f();
	}
	
	Rect(const Vector2f* rectPoints)
	{
		for (unsigned int i = 0; i < c_pointCount; ++i)
			points[i] = rectPoints[i];
	}
	
	Rect (const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, const Vector2f& p4)
	{
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		points[3] = p4;
	}
};

}

#endif
