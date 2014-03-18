#ifndef PHYWORLD_H
#define PHYWORLD_H

#include <Box2D/Box2D.h>
#include "../vector2.hpp"

class PhyWorld: public b2World
{
    public:
        PhyWorld(const Vector2f& gravity);
};

#endif

