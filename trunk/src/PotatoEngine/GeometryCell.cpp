#include "GeometryCell.hpp"
#include "Core/LibsHelpers.hpp"
#include "Debug/Logger.hpp"
#include "Debug/Renderer.hpp"

namespace Pot
{

using Debug::Logger;

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

void GeometryCell::updateAABBs()
{
	if (m_array.getVertexCount() < 1)
	{
		m_localAABB.left = m_localAABB.bottom = m_localAABB.width = m_localAABB.height = 0.f;
		m_worldAABB.left = m_worldAABB.bottom = m_worldAABB.width = m_worldAABB.height = 0.f;
	}
	else
	{
		updateLocalAABB();
		updateWorldAABB();
	}
	
	updateLocalAABBInWorldSpace();
}

void GeometryCell::updateLocalAABB()
{
	const unsigned int vertexCount = m_array.getVertexCount();
	float right = 0.f, top = 0.f;
	m_localAABB.left = right = m_array[0].position.x;
	m_localAABB.bottom = top = m_array[0].position.y;
	
	for (unsigned int i = 1; i < vertexCount; ++i)
	{
		sf::Vector2f& p = m_array[i].position;
		m_localAABB.left = std::min(m_localAABB.left, p.x);
		right = std::max(right, p.x);
		m_localAABB.bottom = std::min(m_localAABB.bottom, p.y);
		top = std::max(top, p.y);
	}
	
	m_localAABB.width = right - m_localAABB.left;
	m_localAABB.height = top - m_localAABB.bottom;
}

void GeometryCell::updateWorldAABB()
{
	const unsigned int vertexCount = m_array.getVertexCount();
	const sf::Transform& localToWorld = sPotato()->worldTransform_const();
	sf::Vector2f transformedPoint = localToWorld.transformPoint(m_array[0].position);
	float right = 0.f, top = 0.f;
	
	m_worldAABB.left = right = transformedPoint.x;
	m_worldAABB.bottom = top = transformedPoint.y;
	
	for (unsigned int i = 1; i < vertexCount; ++i)
	{
		transformedPoint = localToWorld.transformPoint(m_array[i].position);
		m_worldAABB.left = std::min(m_worldAABB.left, transformedPoint.x);
		right = std::max(right, transformedPoint.x);
		m_worldAABB.bottom = std::min(m_worldAABB.bottom, transformedPoint.y);
		top = std::max(top, transformedPoint.y);
	}
	
	m_worldAABB.width = right - m_worldAABB.left;
	m_worldAABB.height = top - m_worldAABB.bottom;
}

void GeometryCell::updateLocalAABBInWorldSpace()
{
	const sf::Transform& localToWorld = sPotato()->worldTransform_const();
	sf::Vector2f p1(m_localAABB.left                    , m_localAABB.bottom                     );
	sf::Vector2f p2(m_localAABB.left + m_localAABB.width, m_localAABB.bottom                     );
	sf::Vector2f p3(m_localAABB.left + m_localAABB.width, m_localAABB.bottom + m_localAABB.height);
	sf::Vector2f p4(m_localAABB.left                    , m_localAABB.bottom + m_localAABB.height);
	
	m_localAABBInWorldSpace.points[0] = localToWorld.transformPoint(p1);
	m_localAABBInWorldSpace.points[1] = localToWorld.transformPoint(p2);
	m_localAABBInWorldSpace.points[2] = localToWorld.transformPoint(p3);
	m_localAABBInWorldSpace.points[3] = localToWorld.transformPoint(p4);
}

void GeometryCell::debugRender(Debug::Renderer& renderer) const
{
	Cell::debugRender(renderer);
	renderer.DrawRect(m_worldAABB, sf::Color::Red);
	renderer.DrawRect(m_localAABBInWorldSpace, sf::Color::Blue);
}

}
