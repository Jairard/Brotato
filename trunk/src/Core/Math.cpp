#include "Math.hpp"

const double Math::RAD_2_DEG = 180./Math::precisePi();

float Math::rad2deg(float angle)
{
	return angle * RAD_2_DEG;
}

float Math::deg2rad(float angle)
{
	return angle / RAD_2_DEG;
}

double Math::precisePi()
{
#ifdef M_PI
	return M_PI;
#else
	return 3.14159265358979323846264338327950288;
#endif
}

float Math::pi()
{
	return (float)precisePi();
}

float Math::lerp(float source, float target, float coef)
{
	coef = clamp<float>(0., 1., coef);
	return (1. - coef) * source + coef * target;
}

Vector2f Math::lerp(const Vector2f& source, const Vector2f& target, float coef)
{
	coef = clamp<float>(0., 1., coef);
	return (1. - coef) * source + coef * target;
}
