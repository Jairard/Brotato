#ifndef __GRAPHICS_POINT_SHAPE__
#define __GRAPHICS_POINT_SHAPE__

#include "../PotatoEngine/Core/Vector2.hpp"
#include "Shape.hpp"

namespace Graphics
{
	class PointShape: public Shape
	{
		public:
			PointShape(const Pot::Vector2f& p=Pot::Vector2f());
			virtual ~PointShape() {}

		protected:
			sf::Vertex&  vertice(void)		{ return m_array[0]; }
	};
}

#endif 
