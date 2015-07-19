#ifndef __GRAPHICS_RECTANGLE_SHAPE__
#define __GRAPHICS_RECTANGLE_SHAPE__

#include "Shape.hpp"

namespace Graphics
{
	class RectangleShape : public Shape
	{
		public:
			RectangleShape(const Pot::Vector2f& pos=Pot::Vector2f(), const Pot::Vector2f& size=Pot::Vector2f(1., 1.));
			virtual ~RectangleShape() {}
			
			void setSize(const Pot::Vector2f& scale);
			void setScale(const Pot::Vector2f& factors);
	};
}

#endif
