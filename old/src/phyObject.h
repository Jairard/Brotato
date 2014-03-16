#ifndef PHYOBJECT_H
#define PHYOBJECT_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "phyWorld.h"
#include "vector2.h"
#include "interpolable.h"

class PhyWorld;

class PhyObject: public Interpolable
{
	public:
		PhyObject(PhyWorld* world);
		virtual ~PhyObject() {}

		virtual void interpolate(float interpolation);
		virtual void update(const Vector2f& pos, double angle) = 0;
		virtual void updateScale(const Vector2f& scale) = 0;

		b2Body* body(void) const	{ return _body; }
		void setBody(b2Body* body)	{ _body = body; }

	protected:
		PhyWorld* _world;
		b2Body* _body;
};

#endif
