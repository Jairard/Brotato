#include "LineGeometry.hpp"
#include "Debug/Logger.hpp"

namespace Pot
{

using Debug::Logger;

LineGeometry::LineGeometry(Potato* potato):
	GeometryCell(potato, sf::Lines, 2)
{
}

void LineGeometry::update()
{
	GeometryCell::update();
	sPotato()->localTransform().rotate(1.f);
	updateAABBs();
}

void LineGeometry::setPoint1(const Vector2f& coords)
{
	m_array[0].position = pv_2_sfv(coords);
	updateAABBs();
}

void LineGeometry::setPoint2(const Vector2f& coords)
{
	m_array[1].position = pv_2_sfv(coords);
	updateAABBs();
}

void LineGeometry::setPoints(const Vector2f& p1, const Vector2f& p2)
{
	m_array[0].position = pv_2_sfv(p1);
	m_array[1].position = pv_2_sfv(p2);
	updateAABBs();
}

void LineGeometry::updateLocalAABB()
{
	const sf::Vector2f& p1 = m_array[0].position;
	const sf::Vector2f& p2 = m_array[1].position;
	
	m_localAABB.left = std::min(p1.x, p2.x);
	m_localAABB.bottom = std::min(p1.y, p2.y);
	m_localAABB.width = fabsf(p1.x - p2.x);
	m_localAABB.height = fabsf(p1.y - p2.y);
}

}
