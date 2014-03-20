#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <Box2D/Box2D.h>
#include "../Vector2.hpp"
#include "World.hpp"
#include "Entity.hpp"

namespace Phy
{	
	class Rectangle: public Entity
	{
		public:
			static const float DEFAULT_DENSITY;
			
			Rectangle(World* world, const Vector2f& center, const Vector2f& size, b2BodyType type);
			
			/*
			virtual void update(const Vector2f& position, float angle);
			//*/
	};
}

#endif
