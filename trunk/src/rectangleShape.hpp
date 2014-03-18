#ifndef PHYRECTANGLE2_H
#define PHYRECTANGLE2_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "vector2.hpp"

class RectangleShape: public sf::RectangleShape
{
	public:
		RectangleShape(b2World* world, sf::Vector2f center, sf::Vector2f size,
					 float angle, const sf::Color& color=sf::Color::White, b2BodyType type = b2_staticBody);
		virtual ~RectangleShape() {}

		b2BodyDef* bodyDef(void)	                         { return &_bodyDef; }
		b2PolygonShape* shape(void)                          { return &_shape; }

		void update(void);

	protected:
		b2Body* _body;
		b2BodyDef _bodyDef;
		b2PolygonShape _shape;
};

#endif
