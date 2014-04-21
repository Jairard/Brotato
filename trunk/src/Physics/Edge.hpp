#ifndef __PHY_EDGE__
#define __PHY_EDGE__

#include "World.hpp"
#include "Entity.hpp"

namespace Phy
{
	class Edge: public Entity
	{
		public:
			Edge(World* world, const Vector2f& p1, const Vector2f& p2, BodyType type);
			virtual ~Edge() {}
			
			virtual b2EdgeShape* shape() const { return (b2EdgeShape*)Entity::shape(); }
	};
}

#endif
