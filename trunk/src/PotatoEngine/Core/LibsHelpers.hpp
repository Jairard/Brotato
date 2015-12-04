#ifndef __POT_CORE_LIBSHELPERS__
#define __POT_CORE_LIBSHELPERS__

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <Box2D/Box2D.h>
#include "AARect.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"

// Vector2 helpers
inline sf::Vector2f b2v_2_sfv(const b2Vec2& b2v)
{
	return sf::Vector2f(b2v.x, b2v.y);
}

inline b2Vec2 sfv_2_b2v(const sf::Vector2f& sfv)
{
	return b2Vec2(sfv.x, sfv.y);
}

inline Pot::Vector2f b2v_2_pv(const b2Vec2& b2v)
{
	return Pot::Vector2f(b2v.x, b2v.y);
}

inline b2Vec2 pv_2_b2v(const Pot::Vector2f& v)
{
	return b2Vec2(v.x, v.y);
}

inline Pot::Vector2f sfv_2_pv(const sf::Vector2f& sfv)
{
	return Pot::Vector2f(sfv.x, sfv.y);
}

inline sf::Vector2f pv_2_sfv(const Pot::Vector2f& v)
{
	return sf::Vector2f(v.x, v.y);
}

// Colors helpers
inline sf::Color b2c_2_sfc(const b2Color& b2c)
{
	const float coef = 255.f;
	return sf::Color(static_cast<sf::Uint8>(b2c.r * coef),
                     static_cast<sf::Uint8>(b2c.g * coef),
                     static_cast<sf::Uint8>(b2c.b * coef));
}

inline b2Color sfc_2_b2c(const sf::Color& sfc)
{
	const float coef = 1.f / 255.f;
	return b2Color(sfc.r * coef, sfc.g * coef, sfc.b *coef);
}

// Rect helpers
inline Pot::AARect sfr_2_paar(const sf::FloatRect& sfr)
{
	// sf::FloatRect's top is the min Y of the rect, so it is Pot::Rect's bottom
	return Pot::AARect(sfr.left, sfr.top, sfr.width, sfr.height);
}

inline sf::FloatRect paar_2_sfr(const Pot::AARect& paar)
{
	return sf::FloatRect(paar.left, paar.bottom, paar.width, paar.height);
}

inline Pot::Rect paar_2_pr(const Pot::AARect& paar)
{
	Pot::Rect res;
	
	res.points[0] = Pot::Vector2f(paar.left             , paar.bottom              );
	res.points[1] = Pot::Vector2f(paar.left + paar.width, paar.bottom              );
	res.points[2] = Pot::Vector2f(paar.left + paar.width, paar.bottom + paar.height);
	res.points[3] = Pot::Vector2f(paar.left             , paar.bottom + paar.height);
	
	return res;
}

inline Pot::Rect sfr_2_pr(const sf::FloatRect& sfr)
{
	return paar_2_pr(sfr_2_paar(sfr));
}

#endif
