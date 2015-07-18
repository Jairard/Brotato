#ifndef __CORE_MATH__
#define __CORE_MATH__

#include <cmath>
#include <SFML/Graphics/Transformable.hpp>
#include "NonInstantiable.hpp"
#include "Vector2_.hpp"

class Math: public NonInstantiable
{
	public:
		static const double RAD_2_DEG;
		static const double DEG_2_RAD;
		
		static float rad2deg(float angle);
		static float deg2rad(float angle);
		static double precisePi(void);
		static float pi(void);
		
		template <typename T>
		static T clamp(const T& min, const T& max, const T& value);
		static float lerp(float source, float target, float coef);
		static Vector2f lerp(const Vector2f& source, const Vector2f& target, float coef);
		static sf::Transformable lerp(const sf::Transformable& source, const sf::Transformable& delta, float coef);
};

template <typename T>
T Math::clamp(const T& min, const T& max, const T& value)
{
	return (value < min ? min : (value > max ? max : value));
}

#endif
