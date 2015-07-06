#include "GeometryCell.hpp"

namespace Pot
{

GeometryCell::GeometryCell(Potato* potato):
	Cell(potato),
	m_array()
{
}

void GeometryCell::setColor(const sf::Color& color)
{
	for (unsigned int i = 0; i < m_array.getVertexCount(); ++i)
		m_array[i].color = color;
}

void GeometryCell::updateAABB()
{
	unsigned int vertexCount = m_array.getVertexCount();
	
	if (vertexCount < 1)
		m_aabb.left = m_aabb.top = m_aabb.width = m_aabb.height = 0.f;
	else
	{
		float right = 0.f, bottom = 0.f;
		m_aabb.left = right = m_array[0].position.x;
		m_aabb.top = bottom = m_array[0].position.y;
		
		for (unsigned int i = 1; i < vertexCount; ++i)
		{
			sf::Vector2f& p = m_array[i].position;
			m_aabb.left = std::min(m_aabb.left, p.x);
			right = std::max(right, p.x);
			// Why not max for top and min for bottom ?
			m_aabb.top = std::max(m_aabb.top, p.y);
			bottom = std::min(bottom, p.y);
		}
		
		m_aabb.width = right - m_aabb.left;
		m_aabb.height = m_aabb.top - bottom;
	}
}

}
