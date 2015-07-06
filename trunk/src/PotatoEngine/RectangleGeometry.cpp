#include "RectangleGeometry.hpp"
#include "Debug/Logger.hpp"

namespace Pot
{

using Debug::Logger;

RectangleGeometry::RectangleGeometry(Potato* potato):
	GeometryCell(potato),
	m_size(1.f, 1.f)
{
	m_array.setPrimitiveType(sf::Quads);
	m_array.resize(4);
	setSize(m_size);
}

void RectangleGeometry::setSize(const Vector2f& size)
{
	const float halfWidth = size.x * 0.5f;
	const float halfHeight = size.y * 0.5f;
	
	m_size = size;
	m_array[0].position = sf::Vector2f(-halfWidth, -halfHeight);
	m_array[1].position = sf::Vector2f( halfWidth, -halfHeight);
	m_array[2].position = sf::Vector2f( halfWidth,  halfHeight);
	m_array[3].position = sf::Vector2f(-halfWidth,  halfHeight);
	
	updateAABB();
}

void RectangleGeometry::updateAABB()
{
	//*
	m_aabb.left = -m_size.x * 0.5f;
	m_aabb.top = m_size.y * 0.5f;
	m_aabb.width = m_size.x;
	m_aabb.height = m_size.y;
	
	Logger::log(Logger::CWarning, "size: %f, %f", m_size.x, m_size.y);
	Logger::log("Warning", "aabb: %f, %f, %F, %f", m_aabb.left, m_aabb.top, m_aabb.width, m_aabb.height);
	/*/
	GeometryCell::updateAABB();
	Logger::log(Logger::CWarning, "size: %f, %f", m_size.x, m_size.y);
	Logger::log("Warning", "aabb: %f, %f, %F, %f", m_aabb.left, m_aabb.top, m_aabb.width, m_aabb.height);
	//*/
}

}
