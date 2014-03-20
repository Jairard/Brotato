#ifndef PHYRECTANGLE2_H
#define PHYRECTANGLE2_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "Vector2.hpp"
#include "Physics/World.hpp"
#include "Physics/Rectangle.hpp"

class RectangleShape: public sf::RectangleShape, public Phy::Rectangle
{
	public:
		RectangleShape(Phy::World* world, sf::Vector2f center, sf::Vector2f size,
					 float angle, const sf::Color& color=sf::Color::White, b2BodyType type = b2_staticBody);
		virtual ~RectangleShape() {}
		
		virtual void update(const Vector2f& position, float angle);
};

#endif
