#include "../Core/Logger.hpp"
#include "SegmentShape.hpp"

namespace Graphics
{
	SegmentShape::SegmentShape():
		Shape(sf::Lines, 2),
		m_center()
	{}

	SegmentShape::SegmentShape(const Vector2f& p1, const Vector2f& p2):
		Shape(sf::Lines, 2),
		m_center()
	{
		setPoints(p1, p2);
	}

	SegmentShape::SegmentShape(const sf::Vector2f& p1, const sf::Vector2f& p2):
		Shape(sf::Lines, 2),
		m_center()
	{
		setFirstPoint(Vector2f(p1.x, p1.y));
		setSecondPoint(Vector2f(p2.x, p2.y));
	}

	SegmentShape::SegmentShape(const Pot::Vector2f& p1, const Pot::Vector2f& p2):
		Shape(sf::Lines, 2),
		m_center()
	{
		setFirstPoint(Vector2f(p1.x, p1.y));
		setSecondPoint(Vector2f(p2.x, p2.y));
	}

	void SegmentShape::setFirstPoint(const Vector2f& p)
	{
		updatePoint(p, 0);
	}

	void SegmentShape::setSecondPoint(const Vector2f& p)
	{
		updatePoint(p, 1);
	}

	void SegmentShape::setPoints(const Vector2f& p1, const Vector2f& p2)
	{
		updatePoints(p1, p2);
		setPosition(m_center.toSFML());
	}

	void SegmentShape::setColors(const sf::Color& c1, const sf::Color& c2)
	{
		m_array[0].color = c1;
		m_array[1].color = c2;
	}
	
	void SegmentShape::toRelativePositions()
	{
		Vector2f p1(m_array[0].position), p2(m_array[1].position);
		m_center = (p1 + p2) / 2.;
		m_array[0].position -= m_center.toSFML();
		m_array[1].position -= m_center.toSFML();
	}
	
	void SegmentShape::toAbsolutePositions()
	{
		m_array[0].position += m_center.toSFML();
		m_array[1].position += m_center.toSFML();
		m_center = Vector2f(0., 0.);
	}
	
	void SegmentShape::updatePoint(const Vector2f& p, int index)
	{
		toAbsolutePositions();
		m_array[index].position = p.toSFML();
		toRelativePositions();
	}
	
	void SegmentShape::updatePoints(const Vector2f& p1, const Vector2f& p2)
	{
		toAbsolutePositions();
		m_array[0].position = p1.toSFML();
		m_array[1].position = p2.toSFML();
		toRelativePositions();
	}
}
