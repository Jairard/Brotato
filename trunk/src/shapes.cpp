#include "shapes.hpp"

SegmentShape::SegmentShape(const sf::Vector2f& p1, const sf::Vector2f& p2):
	_array(sf::Lines, 2)
{
	_array[0].position = p1;
	_array[1].position = p2;
}

void SegmentShape::setFirstPoint(const sf::Vector2f& p)
{
	_array[0].position = p;
}

void SegmentShape::setSecondPoint(const sf::Vector2f& p)
{
	_array[1].position = p;
}

void SegmentShape::setPoints(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
	_array[0].position = p1;
	_array[1].position = p2;
}

void SegmentShape::setColor(const sf::Color& color)
{
	setColor(color, color);
}

void SegmentShape::setColor(const sf::Color& c1, const sf::Color& c2)
{
	_array[0].color = c1;
	_array[1].color = c2;
}

void SegmentShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_array, states);
}

PointShape::PointShape(const sf::Vector2f& p):
	_v()
{
	_v.position = p;
}

void PointShape::setPosition(const sf::Vector2f& pos)
{
	_v.position = pos;
}

void PointShape::setColor(const sf::Color& color)
{
	_v.color = color;
}

void PointShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(&_v, 1, sf::Points);
}

ThickPointShape::ThickPointShape(const sf::RenderWindow* window, const sf::Vector2f center):
	sf::RectangleShape(),
	_thickness(1.),
	_window(window)
{
	setPosition(center);
	update();
}

void ThickPointShape::setThickness(float thickness)
{
	_thickness = thickness;
	update();
}

void ThickPointShape::setColor(const sf::Color& color)
{
	setFillColor(color);
}

void ThickPointShape::update()
{
	float xRatio = _window->getView().getSize().x / (float)_window->getSize().x;
	float yRatio = _window->getView().getSize().y / (float)_window->getSize().y;

	setSize(sf::Vector2f(_thickness, _thickness));
	setOrigin(sf::Vector2f(_thickness, _thickness) / 2.f);
	setScale(sf::Vector2f(xRatio, yRatio));
}

