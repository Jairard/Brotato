#include "PointShape.hpp"

namespace Graphics
{
	PointShape::PointShape(const Pot::Vector2f& p):
		Shape(sf::Points, 1)
	{
		setPosition(p);
	}
}
