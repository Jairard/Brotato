#ifndef __GRAPHICS_POINT_SHAPE__
#define __GRAPHICS_POINT_SHAPE__

#include "../Core/Vector2_.hpp"
#include "Shape.hpp"

namespace Graphics
{
	class PointShape: public Shape
	{
		public:
			PointShape(const Vector2f& p=Vector2f());
			virtual ~PointShape() {}

		protected:
			sf::Vertex&  vertice(void)		{ return m_array[0]; }
	};
}

#endif 
