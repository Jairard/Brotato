#include "Shape.hpp"

namespace Graphics
{
	Shape::Shape(sf::PrimitiveType type, unsigned int vertexCount):
		SFMLEntity(),
		m_array(type, vertexCount)
	{}
	
    /*
	void Shape::setOrigin(const Vector2f& origin)
	{
		setOrigin(origin.toSFML());
	}
	
	void Shape::setPosition(const Vector2f& position)
	{
		setPosition(position.toSFML());
	}
	
	void Shape::setSize(const Vector2f& size)
	{
		setSize(size.toSFML());
	}
    //*/
	
	void Shape::setColor(const sf::Color& color)
	{
		for (unsigned int i=0; i<m_array.getVertexCount(); i++)
			m_array[i].color = color;
	}
	
	void Shape::render(sf::RenderTarget& target, sf::RenderStates states) const
	{
		draw(target, states);
	}
	
	void Shape::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(m_array, states);
	}
}
