#include <cstdio>
#include <math.h>
#include <iostream>

#include "phyWorld.h"
#include "utils.h"

const Vector2f PhyWorld::DEFAULT_GRAVITY = Vector2f(0.0f, 9.81f);
const double PhyWorld::DEFAULT_TIME_STEP = 1./30.;
const unsigned int PhyWorld::DEFAULT_VELOCITY_ITERATIONS = 8;
const unsigned int PhyWorld::DEFAULT_POSITION_ITERATIONS = 3;

PhyWorld::PhyWorld(const Vector2f& gravity, double timeStep, uint32 velocityIt, uint32 positionIt):
	b2World(gravity.toPhy()),
	_timeStep(timeStep),
	_velocityIterations(velocityIt),
	_positionIterations(positionIt)
{}

void PhyWorld::Step()
{
	std::cout << _timeStep << std::endl;
	b2World::Step(_timeStep, _velocityIterations, _positionIterations);

	for (unsigned int i=0; i<_objects.size(); i++)
	{
		PhyObject* obj = _objects[i];
		/*
		Vector2f oldPos = Vector2f(obj->body()->GetPosition()) * (float)scale();
		float32 oldAngle = obj->body()->GetAngle() * (180/M_PI);
		/*/
		Vector2f pos = screenPoint(obj->body()->GetPosition());
		double angle = screenAngle(obj->body()->GetAngle());
		std::cout << "angle : " << obj->body()->GetAngle() << " -> " << angle << std::endl;
		std::cout << "angular velocity : " << obj->body()->GetAngularVelocity() << std::endl;
		//*/

		obj->update(pos, angle);
	}
}

void PhyWorld::setScale(double scale)
{
	setScale(Vector2f(scale, scale));
}

void PhyWorld::setScale(double scaleX, double scaleY)
{
	setScale(Vector2f(scaleX, scaleY));
}

void PhyWorld::setScale(const Vector2f& scale)
{
	sf::Transformable::setScale(scale);
	for (unsigned int i=0; i<_objects.size(); i++)
		_objects[i]->updateScale(scale);
}

Vector2f PhyWorld::screenPoint(const Vector2f& phyPoint) const
{
	return getTransform().transformPoint(phyPoint);
}

Vector2f PhyWorld::phyPoint(const Vector2f& screenPoint) const
{
	return getInverseTransform().transformPoint(screenPoint);
}

double PhyWorld::screenAngle(double phyAngle) const
{
	return phyAngle*(180./M_PI) + getRotation();
}

double PhyWorld::phyAngle(double screenAngle) const
{
	return (screenAngle - getRotation()) * (M_PI/180.);
}

Vector2f PhyWorld::screenVector(const Vector2f& phyVector) const
{
	Vector2f scale(getScale());
	return Vector2f(phyVector.x*scale.x, phyVector.y*scale.y);
}

Vector2f PhyWorld::phyVector(const Vector2f& screenVector) const
{
	Vector2f scale(getScale());
	return Vector2f(screenVector.x/scale.x, screenVector.y/scale.y);
}
