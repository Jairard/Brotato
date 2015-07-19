#ifndef __GAMEOBJECTS_SEGMENT__
#define __GAMEOBJECTS_SEGMENT__

#include "GameObject.hpp"
#include "../Physics/Edge.hpp"
#include "../Graphics/SegmentShape.hpp"

namespace GO
{
	class Segment: public GameObject, public Phy::Edge, public Graphics::SegmentShape
	{
		public:
			Segment(Phy::World* world, Phy::BodyType type,
					const Pot::Vector2f& p1, const Pot::Vector2f& p2);
			virtual ~Segment() {}
			
			virtual void update(const Pot::Vector2f& position, float angle);
	};
}

#endif 
