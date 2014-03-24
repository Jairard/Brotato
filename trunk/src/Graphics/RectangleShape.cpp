#include <iostream>
#include "RectangleShape.hpp"

namespace Graphics
{
	RectangleShape::RectangleShape(const Vector2f& size, const Vector2f& pos):
		Shape(sf::Quads, 4)
	{
		m_array[0].position = sf::Vector2f(    0.,     0.);
		m_array[1].position = sf::Vector2f(size.x,     0.);
		m_array[2].position = sf::Vector2f(size.x, size.y);
		m_array[3].position = sf::Vector2f(    0., size.y);
        
		setOrigin((size/2.).toSFML());
		setPosition(pos.toSFML());
	}
}
