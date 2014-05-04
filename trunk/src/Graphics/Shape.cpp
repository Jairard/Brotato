#include "Shape.hpp"
#include "../Core/Logger.hpp"

namespace Graphics
{
	Shape::Shape(sf::PrimitiveType type, unsigned int vertexCount):
		SFMLEntity(),
		m_array(type, vertexCount)
	{}

	void Shape::setColor(const sf::Color& color)
	{
		for (unsigned int i=0; i<m_array.getVertexCount(); i++)
			m_array[i].color = color;
	}

	void Shape::render(sf::RenderTarget& target, float coef, sf::RenderStates states)
	{
		SFMLEntity::render(target, coef, states);
		draw(target, states);
	}

	void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_array, states);
	}
}
