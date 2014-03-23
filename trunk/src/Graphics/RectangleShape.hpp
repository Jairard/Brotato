#ifndef __GRAPHICS_RECTANGLE_SHAPE__
#define __GRAPHICS_RECTANGLE_SHAPE__

#include "../Vector2.hpp"
#include "Shape.hpp"

namespace Graphics
{	
	class RectangleShape : public Shape
	{
		public:
			RectangleShape(const Vector2f& size=Vector2f(1., 1.), const Vector2f& pos=Vector2f());
			virtual ~RectangleShape() {}
	};
}

#endif
