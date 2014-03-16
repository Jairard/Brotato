#include <iostream>
#include "phyLine.h"

PhyLine::PhyLine(PhyWorld* world, const Vector2f& p1, const Vector2f& p2, double thickness, const sf::Color& color, b2BodyType type):
	LineShape(thickness),
	PhyObject(world)
{
	/* Graphics initialization */
	float scale = 1.;//_world->scale();
	Vector2f v1 = p1*scale, v2 = p2*scale;
	std::cout << v1 << ", " << v2 << std::endl;

	setFirstPoint(p1*scale);
	setSecondPoint(p2*scale);
	//setScale(scale, 1.);
	setFillColor(color);

	/* Physics initialization */
}

void PhyLine::update(const Vector2f& pos, double angle)
{
	setPosition(pos);
	setRotation(_baseAngle + angle);
}
