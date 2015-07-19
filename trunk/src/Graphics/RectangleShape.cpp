#include <iostream>
#include "../PotatoEngine/Core/LibsHelpers.hpp"
#include "RectangleShape.hpp"

namespace Graphics
{
	RectangleShape::RectangleShape(const Pot::Vector2f& pos, const Pot::Vector2f& size):
		Shape(sf::Quads, 4)
	{
		m_array[0].position = sf::Vector2f(-0.5, -0.5);
		m_array[1].position = sf::Vector2f( 0.5, -0.5);
		m_array[2].position = sf::Vector2f( 0.5,  0.5);
		m_array[3].position = sf::Vector2f(-0.5,  0.5);

		setPosition(pos);
		setScale(size);
	}
	
	void RectangleShape::setSize(const Pot::Vector2f& scale)
	{
		setScale(scale);
	}
	
	void RectangleShape::setScale(const Pot::Vector2f& scale)
	{
		sf::Transformable::setScale(pv_2_sfv(scale));
	}
}
