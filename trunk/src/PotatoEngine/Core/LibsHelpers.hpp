#ifndef __LIBSHELPERS__
#define __LIBSHELPERS__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Box2D/Box2D.h>
#include "../../Core/Vector2.hpp"
#include "AARect.hpp"

// Vector2 helpers
inline sf::Vector2f b2v_2_sfv(const b2Vec2& b2v)
{
	return sf::Vector2f(b2v.x, b2v.y);
}

inline b2Vec2 sfv_2_b2v(const sf::Vector2f& sfv)
{
	return b2Vec2(sfv.x, -sfv.y);
}

inline Vector2f b2v_2_pv(const b2Vec2& b2v)
{
	return Vector2f(b2v.x, b2v.y);
}

inline b2Vec2 pv_2_b2v(const sf::Vector2f& v)
{
	return b2Vec2(v.x, v.y);
}

inline Vector2f sfv_2_pv(const sf::Vector2f& sfv)
{
	return Vector2f(sfv.x, sfv.y);
}

inline sf::Vector2f pv_2_sfv(const Vector2f& v)
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

// Rect helpers
inline Pot::AARect sfr_2_pr(const sf::FloatRect& sfr)
{
	// sf::FloatRect's top is the min Y of the rect, so it is Pot::Rect's bottom
	return Pot::AARect(sfr.left, sfr.top, sfr.width, sfr.height);
}

inline sf::FloatRect pr_2_sfr(const Pot::AARect& pr)
{
	return sf::FloatRect(pr.left, pr.bottom, pr.width, pr.height);
}


#endif
