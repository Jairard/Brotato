#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

inline sf::Vector2f sfVec(b2Vec2 v)
{
	return sf::Vector2f(v.x, v.y);
}

inline b2Vec2 phyVec(sf::Vector2f v)
{
	return b2Vec2(v.x, v.y);
}

inline float length(sf::Vector2f v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

#endif
