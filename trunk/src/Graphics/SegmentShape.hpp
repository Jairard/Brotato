#ifndef __GRAPHICS_SEGMENT_SHAPE__
#define __GRAPHICS_SEGMENT_SHAPE__

#include "../Core/Vector2_.hpp"
#include "../PotatoEngine/Core/Vector2.hpp"
#include "Shape.hpp"

namespace Graphics
{
	class SegmentShape: public Shape
	{
		public:
			SegmentShape();
			SegmentShape(const Vector2f& p1, const Vector2f& p2);
			SegmentShape(const sf::Vector2f& p1, const sf::Vector2f& p2);
			SegmentShape(const Pot::Vector2f& p1, const Pot::Vector2f& p2);
			virtual ~SegmentShape() {}
			
			void setFirstPoint(const Vector2f& p);
			void setSecondPoint(const Vector2f& p);
			void setPoints(const Vector2f& p1, const Vector2f& p2);
			void setColors(const sf::Color& c1, const sf::Color& c2);
			
		protected:
			Vector2f m_center;
			
			void toRelativePositions(void);
			void toAbsolutePositions(void);
			void updatePoint(const Vector2f& p, int index);
			void updatePoints(const Vector2f& p1, const Vector2f& p2);
	};
}

#endif
