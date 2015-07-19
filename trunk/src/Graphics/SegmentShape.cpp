#include "../PotatoEngine/Core/LibsHelpers.hpp"
#include "SegmentShape.hpp"

namespace Graphics
{
	SegmentShape::SegmentShape():
		Shape(sf::Lines, 2),
		m_center()
	{}

	SegmentShape::SegmentShape(const sf::Vector2f& p1, const sf::Vector2f& p2):
		Shape(sf::Lines, 2),
		m_center()
	{
		setPoints(sfv_2_pv(p1), sfv_2_pv(p2));
	}

	SegmentShape::SegmentShape(const Pot::Vector2f& p1, const Pot::Vector2f& p2):
		Shape(sf::Lines, 2),
		m_center()
	{
		setPoints(p1, p2);
	}

	void SegmentShape::setFirstPoint(const Pot::Vector2f& p)
	{
		updatePoint(p, 0);
	}

	void SegmentShape::setSecondPoint(const Pot::Vector2f& p)
	{
		updatePoint(p, 1);
	}

	void SegmentShape::setPoints(const Pot::Vector2f& p1, const Pot::Vector2f& p2)
	{
		updatePoints(p1, p2);
		setPosition(m_center);
	}

	void SegmentShape::setColors(const sf::Color& c1, const sf::Color& c2)
	{
		m_array[0].color = c1;
		m_array[1].color = c2;
	}
	
	void SegmentShape::toRelativePositions()
	{
		Pot::Vector2f p1 = sfv_2_pv(m_array[0].position), p2 = sfv_2_pv(m_array[1].position);
		m_center = (p1 + p2) / 2.;
		m_array[0].position -= pv_2_sfv(m_center);
		m_array[1].position -= pv_2_sfv(m_center);
	}
	
	void SegmentShape::toAbsolutePositions()
	{
		m_array[0].position += pv_2_sfv(m_center);
		m_array[1].position += pv_2_sfv(m_center);
		m_center = Pot::Vector2f(0., 0.);
	}
	
	void SegmentShape::updatePoint(const Pot::Vector2f& p, int index)
	{
		toAbsolutePositions();
		m_array[index].position = pv_2_sfv(p);
		toRelativePositions();
	}
	
	void SegmentShape::updatePoints(const Pot::Vector2f& p1, const Pot::Vector2f& p2)
	{
		toAbsolutePositions();
		m_array[0].position = pv_2_sfv(p1);
		m_array[1].position = pv_2_sfv(p2);
		toRelativePositions();
	}
}
