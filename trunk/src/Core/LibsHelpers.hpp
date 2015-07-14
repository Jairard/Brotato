#ifndef __LIBSHELPERS__
#define __LIBSHELPERS__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <Box2D/Box2D.h>
#include "Vector2.hpp"

// Vector2 helpers
inline sf::Vector2f b2v_2_sfv(const b2Vec2& b2v)
{
	return sf::Vector2f(b2v.x, b2v.y);
}

inline b2Vec2 sfv_2_b2v(const sf::Vector2f& sfv)
{
	return b2Vec2(sfv.x, -sfv.y);
}

inline Vector2f b2v_2_v(const b2Vec2& b2v)
{
	return Vector2f(b2v.x, b2v.y);
}

inline b2Vec2 v_2_b2v(const sf::Vector2f& v)
{
	return b2Vec2(v.x, v.y);
}

inline Vector2f sfv_2_v(const sf::Vector2f& sfv)
{
	return Vector2f(sfv.x, sfv.y);
}

inline sf::Vector2f v_2_sfv(const Vector2f& v)
{
	return sf::Vector2f(v.x, v.y);
}

// Colors helpers
inline sf::Color b2c_2_sfc(const b2Color& b2c)
{
	const float coef = 255.f;
	return sf::Color(b2c.r * coef, b2c.g * coef, b2c.b * coef);
}

inline b2Color sfc_2_b2c(const sf::Color& sfc)
{
	const float coef = 1.f / 255.f;
	return b2Color((float)sfc.r * coef, sfc.g * coef, sfc.b *coef);
}

#endif
