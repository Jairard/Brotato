#include "rectangleShape.hpp"

#ifndef M_PI
#define M_PI 3.1415
#endif

RectangleShape::RectangleShape(b2World* world, sf::Vector2f center, sf::Vector2f size, float angle, const sf::Color& color, b2BodyType type):
	sf::RectangleShape(),
	_body(0)
{
	/* Graphics initialization */
	setSize(size);
	setPosition(center);
	setOrigin(size/2.f);
	setFillColor(color);
	setRotation(-angle * 180/M_PI);

	/* Physics initialization */
	_bodyDef.type = type;
	_bodyDef.position.Set(center.x, center.y);
	_bodyDef.angle = angle;
	_bodyDef.allowSleep = true;
	_shape.SetAsBox(size.x/2, size.y/2.);

	_body = world->CreateBody(&_bodyDef);
	b2FixtureDef fixture;
	fixture.shape = &_shape;
	fixture.density = 1.;
	fixture.friction = 0.3f;
	_body->CreateFixture(&fixture);
}

void RectangleShape::update()
{
	Vector2f position = _body->GetPosition();
	float32 angle = _body->GetAngle();

	setPosition(position.x, -position.y);
	setRotation(-angle * 180/M_PI);
}

