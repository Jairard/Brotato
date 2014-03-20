#ifndef __WORLD__
#define __WORLD__

#include <list>
#include <Box2D/Box2D.h>
#include "../Vector2.hpp"

namespace Phy
{
	class Entity;
	
	class World: public b2World
	{
	    public:
			/* Constructors & destructor */
			World(const Vector2f& gravity, float timeStep, int velocityIterations, int positionIterations);
			~World();
			
			/* Accessors */
			
			/* Methods */
			bool RegisterEntity(Entity* entity, bool secure = false);
			bool UnregisterEntity(Entity* entity, bool secure = false);
			
			void step(void);
			
			virtual Vector2f vectorFromPhy(const Vector2f& v);
			virtual Vector2f vectorToPhy(const Vector2f v);
			virtual float angleFromPhy(float angle);
			virtual float angleToPhy(float angle);
			
			
		protected:
			std::list<Entity*> m_entities;
			float m_timeStep;
			int m_velocityIterations, m_positionIterations;
	};
}

#endif

