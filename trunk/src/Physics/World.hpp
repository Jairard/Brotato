#ifndef __PHY_WORLD__
#define __PHY_WORLD__

#include <list>
#include <Box2D/Box2D.h>
#include "../PotatoEngine/Core/Vector2.hpp"

namespace Phy
{
	class Entity;
	
	typedef enum BodyType
	{
		Dynamic,
		Kinematic,
		Static
	} BodyType;

	class World: public b2World
	{
		public:
			/* Constructors & destructor */
			World(const Pot::Vector2f& gravity, float timeStep, int velocityIterations, int positionIterations);
			~World();

			/* Accessors */
			float timestep() const  { return m_timeStep; }

			/* Methods */
			bool RegisterEntity(Entity* entity, bool secure = false);
			bool UnregisterEntity(Entity* entity, bool secure = false);

			void setDebugRenderer(b2Draw* renderer);
			void unsetDebugRenderer(void);
			void step(void);

			static Pot::Vector2f vectorFromPhy(const Pot::Vector2f& v);
			static Pot::Vector2f vectorToPhy(const Pot::Vector2f v);
			static float angleFromPhy(float angle);
			static float angleToPhy(float angle);
			static b2BodyType toBox2DType(BodyType type);

		protected:
			std::list<Entity*> m_entities;
			float m_timeStep;
			int m_velocityIterations, m_positionIterations;
			bool m_drawDebug;
	};
}

#endif

