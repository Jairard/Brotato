#include "Edge.hpp"
#include "../PotatoEngine/Core/LibsHelpers.hpp"

namespace Phy
{
	Edge::Edge(World* world, const Pot::Vector2f& p1, const Pot::Vector2f& p2, BodyType type):
		Entity(world)
	{
		Pot::Vector2f center = (p1 + p2)/2.;
		
		m_bodyDef.type = World::toBox2DType(type);
		m_bodyDef.position = pv_2_b2v(center);
		m_bodyDef.allowSleep = true;
		
		b2EdgeShape* shape = new b2EdgeShape();
		shape->m_vertex1 = pv_2_b2v(p1 - center);
		shape->m_vertex2 = pv_2_b2v(p2 - center);
		shape->m_hasVertex0 = false;
		shape->m_hasVertex3 = false;
		m_shape = shape;
		
		m_fixtureDef.shape = m_shape;
		m_fixtureDef.density = DEFAULT_DENSITY;
	}
}
