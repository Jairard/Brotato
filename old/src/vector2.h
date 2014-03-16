#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

template <typename T> class Vector2: public sf::Vector2<T>
{
	public :
		Vector2():                        sf::Vector2<T>() {}
		Vector2(T x, T y):                sf::Vector2<T>(x, y) {}
		Vector2(const sf::Vector2<T>& v): sf::Vector2<T>(v.x, v.y) {}
		Vector2(const b2Vec2& v):         sf::Vector2<T>(v.x, v.y) {}

		b2Vec2 toPhy(void) const;
		double squaredLength(void) const;
		double length(void) const;
		T crossProduct(const Vector2<T>& other) const;
};

template <typename T>
b2Vec2 Vector2<T>::toPhy() const
{
	return b2Vec2(this->x, this->y);
}

template <typename T>
double Vector2<T>::squaredLength() const
{
	return this->x*this->x + this->y*this->y;
}

template <typename T>
double Vector2<T>::length() const
{
	return sqrt(squaredLength());
}

template <typename T>
T Vector2<T>::crossProduct(const Vector2<T>& other) const
{
	return this->x*other.y - this->y*other.x;
}

template <typename T>
T operator*(const Vector2<T>& left, const Vector2<T>& right)
{
	return left.x*right.x + left.y*right.y;
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v)
{
	stream << "(" << v.x << ", " << v.y << ")";
	return stream;
}

typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;

#endif
