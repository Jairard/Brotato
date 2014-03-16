#include "phyRectangle.h"

PhyRectangle::PhyRectangle(PhyWorld* world, sf::Vector2f center, sf::Vector2f size, const sf::Color& color, b2BodyType type):
	sf::RectangleShape(),
	PhyObject(world)
{
	/* Graphics initialization */
	setSize(size);
	setPosition(world->screenPoint(center));
	setScale(world->getScale());
	setOrigin(size/2.f);
	setFillColor(color);

	/* Physics initialization */
	_bodyDef.type = type;
	_bodyDef.position.Set(center.x, center.y);
	_bodyDef.allowSleep = true;
	_shape.SetAsBox(size.x/2, size.y/2.);

	b2Body* body = _world->CreateBody(&_bodyDef);
	b2FixtureDef fixture;
	fixture.shape = &_shape;
	body->CreateFixture(&fixture);

	setBody(body);
}

std::vector<b2Fixture*> PhyRectangle::fixtures() const
{
	std::vector<b2Fixture*> fix;

	for (b2Fixture* f=_body->GetFixtureList(); f; f=f->GetNext())
		fix.push_back(f);

	return fix;
}

void PhyRectangle::update(const Vector2f& pos, double angle)
{
	setPosition(pos);
	setRotation(angle);
}

void PhyRectangle::updateScale(const Vector2f& scale)
{
	setScale(scale);
}

