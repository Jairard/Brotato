#include <iostream>
#include "Physics/Entity.hpp"
#include "RectangleShape.hpp"
#include "Math.hpp"

RectangleShape::RectangleShape(Phy::World* world, sf::Vector2f center, sf::Vector2f size, float angle, const sf::Color& color, b2BodyType type):
	sf::RectangleShape(),
	Phy::Rectangle(world, center, size, type)/*,
	_body(0)*/
{
	/* Physics initialization */
	bodyDef().angle = angle;

	/* Graphics initialization */
	Vector2f realSize = Vector2f(size) + 2*shape()->m_radius;
	setSize(realSize.toSFML());
	setPosition(center);
	setOrigin(realSize.toSFML()/2.f);
	setFillColor(color);
	setRotation(-angle * 180/Math::pi());
}

void RectangleShape::update(const Vector2f& position, float angle)
{
	setPosition(position.toSFML());
	setRotation(angle);
}

