#include "../stdafx.h"
#include "Math.hpp"
#include "LibsHelpers.hpp"

namespace Pot
{

const double Math::RAD_2_DEG = 180. / Math::precisePi();
const double Math::DEG_2_RAD = Math::precisePi() / 180.;

float Math::rad2deg(float angle)
{
	return angle * static_cast<float>(RAD_2_DEG);
}

float Math::deg2rad(float angle)
{
	return angle * static_cast<float>(DEG_2_RAD);
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
	return static_cast<float>(precisePi());
}

float Math::lerp(float source, float target, float coef)
{
	coef = clamp<float>(0.f, 1.f, coef);
	return (1.f - coef) * source + coef * target;
}

Vector2f Math::lerp(const Vector2f& source, const Vector2f& target, float coef)
{
	coef = clamp<float>(0.f, 1.f, coef);
	return (1.f - coef) * source + coef * target;
}

}
