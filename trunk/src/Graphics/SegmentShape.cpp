#include "SegmentShape.hpp"

namespace Graphics
{
	SegmentShape::SegmentShape(const Vector2f& p1, const Vector2f& p2):
		Shape(sf::Lines, 2)
	{
		setPoints(p1, p2);
	}
	
	void SegmentShape::setFirstPoint(const Vector2f& p)
	{
		m_array[0].position = p.toSFML();
	}
	
	void SegmentShape::setSecondPoint(const Vector2f& p)
	{
		m_array[1].position = p.toSFML();
	}
	
	void SegmentShape::setPoints(const Vector2f& p1, const Vector2f& p2)
	{
		setFirstPoint(p1);
		setSecondPoint(p2);
	}
	
	void SegmentShape::setColors(const sf::Color& c1, const sf::Color& c2)
	{
		m_array[0].color = c1;
		m_array[1].color = c2;
	}
}
