#include <iostream>
#include "RectangleShape.hpp"

namespace Graphics
{
	RectangleShape::RectangleShape(const Vector2f& pos, const Vector2f& size):
		Shape(sf::Quads, 4)
	{
		m_array[0].position = sf::Vector2f(-0.5, -0.5);
		m_array[1].position = sf::Vector2f( 0.5, -0.5);
		m_array[2].position = sf::Vector2f( 0.5,  0.5);
		m_array[3].position = sf::Vector2f(-0.5,  0.5);

		setPosition(pos.toSFML());
		setScale(size.toSFML());
	}
	
	void RectangleShape::setSize(const Vector2f& scale)
	{
		setScale(scale);
	}
	
	void RectangleShape::setScale(const Vector2f& scale)
	{
		sf::Transformable::setScale(scale.toSFML());
	}
}
