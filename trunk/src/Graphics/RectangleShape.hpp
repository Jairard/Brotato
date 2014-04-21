#ifndef __GRAPHICS_RECTANGLE_SHAPE__
#define __GRAPHICS_RECTANGLE_SHAPE__

#include "../Core/Vector2.hpp"
#include "Shape.hpp"

namespace Graphics
{
	class RectangleShape : public Shape
	{
		public:
			RectangleShape(const Vector2f& pos=Vector2f(), const Vector2f& size=Vector2f(1., 1.));
			virtual ~RectangleShape() {}
			
			void setSize(const Vector2f& scale);
			//void setScale(const Vector2f& factors);
	};
}

#endif
