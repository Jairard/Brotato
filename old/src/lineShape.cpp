#include <math.h>
#include <iostream>

#include "lineShape.h"
#include "utils.h"

const Vector2f LineShape::_ref(1., 0.);

LineShape::LineShape(double thickness):
	sf::RectangleShape()
{
	init(Vector2f(), Vector2f(), thickness);
}

LineShape::LineShape(float x0, float y0, float x1, float y1, double thickness):
	sf::RectangleShape()
{
	init(Vector2f(x0, y0), Vector2f(x1, y1), thickness);
}

LineShape::LineShape(const Vector2f& p1, const Vector2f& p2, double thickness):
	sf::RectangleShape()
{
	init(p1, p2, thickness);
}

void LineShape::init(const Vector2f& p1, const Vector2f& p2, double thickness)
{
	_p1 = p1;
	_p2 = p2;
	_r1 = 0;
	_r2 = 0;
	_thickness = thickness;
	_baseAngle = 0.;

	updatePositions();
	updateThickness();
}

void LineShape::updatePositions()
{
	if (_p1.x <= _p2.x)
	{
		_r1 = &_p1;
		_r2 = &_p2;
	}
	else
	{
		_r1 = &_p2;
		_r2 = &_p1;
	}
	_center = (_p1 + _p2) / 2.f;

	Vector2f line = *_r2-*_r1;
	float l = line.length();
	float cos = (_ref*line) / (_ref.length() * l);
	_baseAngle = acos(cos) * 180./M_PI;

	if (_ref.crossProduct(line) < 0)
		_baseAngle = -_baseAngle;

	Vector2f size(getSize());
	size.x = l;

	setSize(size);
	setOrigin(size/2.f);
	setPosition(_center);
	setRotation(_baseAngle);
}

void LineShape::setFirstPoint(const Vector2f& p)
{
	_p1 = p;
	updatePositions();
}

void LineShape::setSecondPoint(const Vector2f& p)
{
	_p2 = p;
	updatePositions();
}

void LineShape::setThickness(double thickness)
{
	_thickness = thickness;
	updateThickness();
}

void LineShape::updateThickness()
{
	Vector2f size(getSize().x, _thickness);
	setSize(size);
	setOrigin(size/2.f);
}
