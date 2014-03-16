#ifndef PHYLINE_H
#define PHYLINE_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "vector2.h"
#include "phyWorld.h"
#include "phyObject.h"
#include "lineShape.h"

class PhyLine: public LineShape, public PhyObject
{
	public:
		PhyLine(PhyWorld* world, const Vector2f& p1, const Vector2f& p2, double thickness=1.,
				const sf::Color& color=sf::Color::White, b2BodyType type = b2_staticBody);
		virtual ~PhyLine() {}

		virtual void update(const Vector2f& pos, double angle);
		virtual void updateScale(const Vector2f& scale) {}
};

#endif
