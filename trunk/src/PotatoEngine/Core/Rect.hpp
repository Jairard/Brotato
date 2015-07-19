#ifndef __RECT__
#define __RECT__

#include "Vector2.hpp"
#include "AARect.hpp"

namespace Pot
{

struct Rect
{
	static const unsigned int c_pointCount = 4;
	// TODO: check if this is legit
	Vector2f points[c_pointCount];
	
	Rect()
	{
		for (unsigned int i = 0; i < c_pointCount; ++i)
			points[i] = Vector2f();
	}
	
	Rect(const Rect& other)
	{
		for (unsigned int i = 0; i < c_pointCount; ++i)
			points[i] = other.points[i];
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
	
	AARect AABB() const
	{
		AARect aabb;
		float right, top;
		aabb.left = right = points[0].x;
		aabb.bottom = top = points[0].y;
		
		for (unsigned int i = 1; i < c_pointCount; ++i)
		{
			aabb.left = std::min(aabb.left, points[i].x);
			right = std::max(right, points[i].x);
			aabb.bottom = std::min(aabb.bottom, points[i].y);
			top = std::max(top, points[i].y);
		}
		
		aabb.width = right - aabb.left;
		aabb.height = top - aabb.bottom;
		
		return aabb;
	}
	
	bool operator==(const Rect& other)
	{
		for (unsigned int i = 0; i < c_pointCount; ++i)
		{
			if (points[i].x != other.points[i].x ||
			    points[i].y != other.points[i].y)
			{
				return false;
			}
		}
		
		return true;
	}
	
	Rect& operator=(const Rect& other)
	{
		for (unsigned int i = 0; i < c_pointCount; ++i)
			points[i] = other.points[i];
		
		return *this;
	}
};

}

#endif
