#include <stdafx.h>
#include <GeometryCell.hpp>

#include <Core/LibsHelpers.hpp>
#include <Debug/Logger.hpp>
#include <Debug/Renderer.hpp>

namespace Pot
{

using Debug::Logger;

GeometryCell::GeometryCell(Potato* potato, sf::PrimitiveType primitiveType, size_t vertexCount):
	Cell(potato),
	m_array(primitiveType, vertexCount)
{
}

void GeometryCell::setColor(const sf::Color& color)
{
	for (size_t i = 0; i < m_array.getVertexCount(); ++i)
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
	ASSERT_RELEASE(m_array.getVertexCount() > 0);
	const size_t vertexCount = m_array.getVertexCount();
	float right = 0.f, top = 0.f;
	m_localAABB.left = right = m_array[0].position.x;
	m_localAABB.bottom = top = m_array[0].position.y;
	
	for (size_t i = 1; i < vertexCount; ++i)
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
	ASSERT_RELEASE(m_array.getVertexCount() > 0);
	const size_t vertexCount = m_array.getVertexCount();
	const Transform& localToWorld = sPotato()->localToWorldTransform();
	Vector2f transformedPoint = localToWorld.transformPoint(sfv_2_pv(m_array[0].position));
	float right = 0.f, top = 0.f;
	
	m_worldAABB.left = right = transformedPoint.x;
	m_worldAABB.bottom = top = transformedPoint.y;
	
	for (size_t i = 1; i < vertexCount; ++i)
	{
		transformedPoint = localToWorld.transformPoint(sfv_2_pv(m_array[i].position));
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
	m_localAABBInWorldSpace = sPotato()->localToWorldTransform().transformRect(m_localAABB);
}

void GeometryCell::debugRender(Debug::Renderer& renderer) const
{
	Cell::debugRender(renderer);
	renderer.DrawRect(m_localAABBInWorldSpace, sf::Color::Blue);
	renderer.DrawRect(m_worldAABB, sf::Color::Red);
}

}
