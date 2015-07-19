#include <iostream>
#include "Rectangle.hpp"

namespace Phy
{
	Rectangle::Rectangle(World* world, const Pot::Vector2f& center, const Pot::Vector2f& size, BodyType type) :
		Entity(world)
	{
		m_bodyDef.type = World::toBox2DType(type);
		m_bodyDef.position.Set(center.x, center.y);
		m_bodyDef.allowSleep = true;

		Pot::Vector2f halfSize = size/2.;
		b2PolygonShape* shape = new b2PolygonShape();
		shape->SetAsBox(halfSize.x, halfSize.y);
		m_shape = shape;

		m_fixtureDef.shape = m_shape;
		m_fixtureDef.density = DEFAULT_DENSITY;
	}
}
