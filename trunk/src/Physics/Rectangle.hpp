#ifndef __PHY_RECTANGLE__
#define __PHY_RECTANGLE__

#include <Box2D/Box2D.h>
#include "../Core/Vector2_.hpp"
#include "World.hpp"
#include "Entity.hpp"

namespace Phy
{
	class Rectangle: public Entity
	{
		public:
			Rectangle(World* world, const Vector2f& center, const Vector2f& size, BodyType type);
			virtual ~Rectangle() {}
			
			virtual b2PolygonShape* shape() const { return (b2PolygonShape*)Entity::shape(); }

			/*
			virtual void update(const Vector2f& position, float angle);
			virtual void setup(void);
			//*/
	};
}

#endif
