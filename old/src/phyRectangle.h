#ifndef PHYRECTANGLE2_H
#define PHYRECTANGLE2_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "vector2.h"
#include "phyWorld.h"
#include "phyObject.h"

class PhyRectangle: public sf::RectangleShape, public PhyObject
{
	public:
		PhyRectangle(PhyWorld* world, sf::Vector2f center, sf::Vector2f size,
					 const sf::Color& color=sf::Color::White, b2BodyType type = b2_staticBody);
		virtual ~PhyRectangle() {}

		b2BodyDef* bodyDef()	                         { return &_bodyDef; }
		b2PolygonShape* shape()                          { return &_shape; }
		std::vector<b2Fixture*> fixtures(void) const;

		virtual void update(const Vector2f& pos, double angle);
		virtual void updateScale(const Vector2f& scale);

	protected:
		b2BodyDef _bodyDef;
		b2PolygonShape _shape;
};

#endif
