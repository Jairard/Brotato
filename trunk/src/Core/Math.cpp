#include "Math.hpp"

const double Math::RAD_2_DEG = 180. / Math::precisePi();
const double Math::DEG_2_RAD = Math::precisePi() / 180.;

float Math::rad2deg(float angle)
{
	return angle * RAD_2_DEG;
}

float Math::deg2rad(float angle)
{
	return angle * DEG_2_RAD;
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

sf::Transformable Math::lerp(const sf::Transformable& source, const sf::Transformable& delta, float coef)
{
	sf::Transformable res;
	const sf::Vector2f& srcPos = source.getPosition(),
	                    srcScale = source.getScale();
	float srcRot = source.getRotation();
	
	Vector2f resPos = Math::lerp(srcPos, srcPos + delta.getPosition(), coef),
	         resScale = Math::lerp(srcScale, srcScale + delta.getScale(), coef);
	
	res.setPosition(resPos.x, resPos.y);
	res.setScale(resScale.x, resScale.y);
	res.setRotation(Math::lerp(srcRot, srcRot + delta.getRotation(), coef));
	
	return res;
}
