#include <iostream>
#include "phyWorld.h"
#include "phyObject.h"

PhyObject::PhyObject(PhyWorld* world):
	_world(world),
	_body(0)
{
	_world->addObject(this);
}

void PhyObject::interpolate(float interpolation)
{
	Vector2f currentPosition(_body->GetPosition());
	Vector2f nextPosition = currentPosition + (float)_world->timeStep() * Vector2f(_body->GetLinearVelocity());
	double currentAngle = _body->GetAngle();
	double nextAngle = currentAngle + (float)_world->timeStep() * _body->GetAngularVelocity();

	Vector2f pos = currentPosition + interpolation * (nextPosition-currentPosition);
	double angle = currentAngle + interpolation * (nextAngle-currentAngle);

	//std::cout << "Velocity : " << Vector2f(_body->GetLinearVelocity()) << std::endl;
	//std::cout << currentPosition << " -> " << nextPosition << std::endl;

	update(_world->screenPoint(pos), _world->screenAngle(angle));
}
