#ifndef __ENTITY__
#define __ENTITY__

#include <Box2D/Box2D.h>
#include "../Vector2.hpp"

namespace Phy
{
	class World;
	
	class Entity
	{
		public:
			/* Constructors & desctructor */
			Entity(World* world, bool secure = false);
			virtual ~Entity();
	
			/* Accessors */
			World*				world()	const			{ return m_world; }
			b2Body*				body() const			{ return m_body; }
			b2Shape*			shape()	const			{ return m_shape; }
			b2Fixture*			shapeFixture() const	{ return m_shapeFixture; }
			const b2BodyDef&	bodyDef() const			{ return m_bodyDef; }
			const b2FixtureDef&	fixtureDef() const		{ return m_fixtureDef; }
			b2BodyDef&			bodyDef()				{ return m_bodyDef; }
			b2FixtureDef&		fixtureDef()			{ return m_fixtureDef; }
			const Vector2f&		position() const		{ return m_position; }
			float				angle() const			{ return m_angle; }
			
			/* Methods */
			virtual void build(void);
			virtual void update(const Vector2f& position, float angle);
	
		protected:
			bool m_isSecure;
			
			/* Physics members */
			World* m_world;
			b2Body* m_body;
			b2Shape* m_shape;
			b2Fixture* m_shapeFixture;
			b2BodyDef m_bodyDef;
			b2FixtureDef m_fixtureDef;
			
			/* Geomtrics members */
			Vector2f m_position;
			float m_angle;
	};
}

#endif
