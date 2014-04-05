#include "Entity.hpp"
#include "World.hpp"

namespace Phy
{
	Entity::Entity(World* world, bool isSecure):
		m_isSecure(isSecure),
		m_world(world),
		m_body(0),
		m_shape(0),
		m_shapeFixture(0),
		m_isSetup(false),
		m_position(),
		m_angle(0.)
	{}
	
	Entity::~Entity()
	{
		if (m_shape)
			delete m_shape;
	}
	
	void Entity::setup()
	{	
		if (m_isSetup)
			return;
		
		// Creates body
		m_body = m_world->CreateBody(&m_bodyDef);
		// Attaches collision shape to body
		m_shapeFixture = m_body->CreateFixture(&m_fixtureDef);
		m_isSetup = true;
	}
	
	void Entity::update(const Vector2f &position, float angle)
	{
		m_position = position;
		m_angle = angle;
	}
}
