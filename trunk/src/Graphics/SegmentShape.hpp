#ifndef __GRAPHICS_SEGMENT_SHAPE__
#define __GRAPHICS_SEGMENT_SHAPE__

#include "../Core/Vector2.hpp"
#include "Shape.hpp"

namespace Graphics
{
	class SegmentShape: public Shape
	{
		public:
			SegmentShape(const Vector2f& p1=Vector2f(), const Vector2f& p2=Vector2f());
			virtual ~SegmentShape() {}

			void setFirstPoint(const Vector2f& p);
			void setSecondPoint(const Vector2f& p);
			void setPoints(const Vector2f& p1, const Vector2f& p2);
			void setColors(const sf::Color& c1, const sf::Color& c2);
	};
}

#endif
