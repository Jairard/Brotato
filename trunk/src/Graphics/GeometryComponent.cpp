#include "GeometryComponent.hpp"

namespace Graphics
{
	GeometryComponent::GeometryComponent(sf::PrimitiveType type, unsigned int vertexCount):
		Component(),
		m_array(type, vertexCount)
	{
		
	}
	
	GeometryComponent::~GeometryComponent()
	{
	}
	
	void GeometryComponent::setColor(const sf::Color& color)
	{
		for (unsigned int i=0; i<m_array.getVertexCount(); i++)
			m_array[i].color = color;
	}
}
