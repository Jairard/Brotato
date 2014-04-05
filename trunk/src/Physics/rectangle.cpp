#include <iostream>
#include "Rectangle.hpp"

namespace Phy
{
	const float Rectangle::DEFAULT_DENSITY = 1.;

	Rectangle::Rectangle(World* world, const Vector2f& center, const Vector2f& size, BodyType type) :
		Entity(world)
	{
		m_bodyDef.type = World::toBox2DType(type);
		m_bodyDef.position.Set(center.x, center.y);
		m_bodyDef.allowSleep = true;

		Vector2f halfSize = size/2.;
		b2PolygonShape* shape = new b2PolygonShape();
		shape->SetAsBox(halfSize.x, halfSize.y);
		m_shape = shape;

		m_fixtureDef.shape = m_shape;
		m_fixtureDef.density = DEFAULT_DENSITY;
	}
}
