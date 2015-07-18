#ifndef __VECTOR2__
#define __VECTOR2__

#include <iostream>
#include <cmath>

#ifndef ZERO
# define ZERO	1E-15
#endif

namespace Pot
{

template <typename T> class Vector2
{
	public:
		T x, y;

		Vector2(const T& _x=0, const T& _y=0):
			x(_x), y(_y) 
		{}

		template <typename U>
		Vector2(const Vector2<U>& v):	
			x((T)v.x), y((T)v.y)
		{}

		template <typename U>
		Vector2(const sf::Vector2<U>& v):
			x((T)v.x), y((T)v.y)
		{}

		bool isNull(void) const;
		T squareLength(void) const;
		double length(void) const;
		const Vector2<T>& normalize(void);
		template <typename U> 
		T crossProduct(const Vector2<U>& other) const;
		template <typename U>
		T dot(const Vector2<U>& other) const;
		void setLength(double length);
		template <typename U>
		Vector2<T>& clamp(const U& min, const U& max);
};

template <typename T>
bool Vector2<T>::isNull() const
{
	return fabs(squareLength()) < ZERO * ZERO;
}

template <typename T>
T Vector2<T>::squareLength() const
{
	return dot(*this);
}

template <typename T>
double Vector2<T>::length() const
{
	return sqrt(squareLength());
}

template <typename T>
const Vector2<T>& Vector2<T>::normalize()
{
	if (!isNull())
		*this /= length();
	return *this;
}

template <typename T> template <typename U>
T Vector2<T>::crossProduct(const Vector2<U>& other) const
{
	return x*(T)other.y - y*(T)other.x;
}

template <typename T> template <typename U>
T Vector2<T>::dot(const Vector2<U>& other) const
{
	return x*(T)other.x + y*(T)other.y;
}

template <typename T>
void Vector2<T>::setLength(double length)
{
	normalize();
	*this *= length;
}

template <typename T> template <typename U>
Vector2<T>& Vector2<T>::clamp(const U& min, const U& max)
{
	T _min = (T)min, _max = (T)max;

	x = (x < _min ? _min : (x > _max ? _max : x));
	y = (y < _min ? _min : (y > _max ? _max : y));

	return *this;
}

/* Unary - */
template <typename T>
Vector2<T> operator-(const Vector2<T>& v)
{
	return Vector2<T>(-v.x, -v.y);
}

/* arithmetical operators with U */
template <typename T, typename U>
Vector2<T> operator+(const Vector2<T>& v, const U& c)
{
	return Vector2<T>(v.x+(T)c, v.y+(T)c);
}

template <typename T, typename U>
Vector2<T> operator+(const U& c, const Vector2<T>& v)
{
	return v+c;
}

template <typename T, typename U>
Vector2<T>& operator+=(Vector2<T>& v, const U& c)
{
	v.x += (T)c;
	v.y += (T)c;

	return v;
}

template <typename T, typename U>
Vector2<T> operator-(const Vector2<T>& v, const U& c)
{
	return Vector2<T>(v.x-(T)c, v.y-(T)c);
}

template <typename T, typename U>
Vector2<T> operator-(const U& c, const Vector2<T>& v)
{
	return -(v-c);
}

template <typename T, typename U>
Vector2<T>& operator-=(Vector2<T>& v, const U& c)
{
	v.x -= (T)c;
	v.y -= (T)c;

	return v;
}

template <typename T, typename U>
Vector2<T> operator*(const Vector2<T>& v, const U& c)
{
	return Vector2<T>(v.x*(T)c, v.y*(T)c);
}

template <typename T, typename U>
Vector2<T> operator*(const U& c, const Vector2<T>& v)
{
	return v*c;
}

template <typename T, typename U>
Vector2<T>& operator*=(Vector2<T>& v, const U& c)
{
	v.x *= (T)c;
	v.y *= (T)c;

	return v;
}

template <typename T, typename U>
Vector2<T> operator/(const Vector2<T>& v, const U& c)
{
	return Vector2<T>(v.x/(T)c, v.y/(T)c);
}

template <typename T, typename U>
Vector2<T> operator/(const U& c, const Vector2<T>& v)
{
	return 1./(v/c);
}

template <typename T, typename U>
Vector2<T>& operator/=(Vector2<T>& v, const U& c)
{
	v.x /= (T)c;
	v.y /= (T)c;

	return v;
}

/* arithmetical operatos with Vectors */
template <typename T, typename U>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<U>& right)
{
	return Vector2<T>(left.x+(T)right.x, left.y+(T)right.y);
}

template <typename T, typename U>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<U>& right)
{
	left.x += (T)right.x;
	left.y += (T)right.y;

	return left;
}

template <typename T, typename U>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<U>& right)
{
	return Vector2<T>(left.x-(T)right.x, left.y-(T)right.y);
}

template <typename T, typename U>
Vector2<T>& operator-=(Vector2<T>& left, const Vector2<U>& right)
{
	left.x -= (T)right.x;
	left.y -= (T)right.y;

	return left;
}

template <typename T, typename U>
Vector2<T> operator*(const Vector2<T>& left, const Vector2<U>& right)
{
	return Vector2<T>(left.x*(T)right.x, left.y*(T)right.y);
}

template <typename T, typename U>
Vector2<T>& operator*=(Vector2<T>& left, const Vector2<U>& right)
{
	left.x *= (T)right.x;
	left.y *= (T)right.y;

	return left;
}

template <typename T, typename U>
Vector2<T> operator/(const Vector2<T>& left, const Vector2<U>& right)
{
	return Vector2<T>(left.x/(T)right.x, left.y/(T)right.y);
}

template <typename T, typename U>
Vector2<T>& operator/=(Vector2<T>& left, const Vector2<U>& right)
{
	left.x /= (T)right.x;
	left.y /= (T)right.y;

	return left;
}

template <typename T, typename U>
Vector2<T> operator^(const Vector2<T>& left, const Vector2<U>& right)
{
	return left.crossProduct(Vector2<T>(right));
}

template <typename T, typename U>
Vector2<T> operator^=(Vector2<T>& left, const Vector2<U>& right)
{
	return left = left^right;
}

/* stream operator */
template <typename T>
std::ostream& operator<<(std::ostream& stream, const Vector2<T>& v)
{
	stream << "(" << v.x << ", " << v.y << ")";
	return stream;
}

typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;

}

#endif
