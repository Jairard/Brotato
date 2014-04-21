#include "Edge.hpp"
#include "../Core/Logger.hpp"

namespace Phy
{
	Edge::Edge(World* world, const Vector2f& p1, const Vector2f& p2, BodyType type):
		Entity(world)
	{
		Vector2f center = (p1 + p2)/2.;
		
		m_bodyDef.type = World::toBox2DType(type);
		m_bodyDef.position = center.toBox2D();
		m_bodyDef.allowSleep = true;
		
		b2EdgeShape* shape = new b2EdgeShape();
		shape->m_vertex1 = (p1 - center).toBox2D();
		shape->m_vertex2 = (p2 - center).toBox2D();
		shape->m_hasVertex0 = false;
		shape->m_hasVertex3 = false;
		m_shape = shape;
		
		m_fixtureDef.shape = m_shape;
		m_fixtureDef.density = DEFAULT_DENSITY;
	}
}
