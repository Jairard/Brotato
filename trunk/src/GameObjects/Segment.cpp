#include "Segment.hpp"

namespace GO
{
	Segment::Segment(Phy::World* world, Phy::BodyType type,
	                 const Pot::Vector2f& p1, const Pot::Vector2f& p2):
		GameObject(),
		Phy::Edge(world, p1, p2, type),
		Graphics::SegmentShape()
	{
		/* Physics initialization */
		world->RegisterEntity(this, m_isSecure);
		
		/* Graphics initialization */
		setPoints(Phy::World::vectorFromPhy(p1), Phy::World::vectorFromPhy(p2));
	}
	
	void Segment::update(const Pot::Vector2f& position, float angle)
	{
		Phy::Edge::update(position, angle);
		Graphics::SegmentShape::onGameUpdate(position, angle);
	}
}
