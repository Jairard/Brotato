#include "PointShape.hpp"

namespace Graphics
{
	PointShape::PointShape(const Vector2f& p):
		Shape(sf::Points, 1)
	{
		setPosition(p.toSFML());
	}
}
