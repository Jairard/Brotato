#include "phyWorld.hpp"

PhyWorld::PhyWorld(const Vector2f& gravity):
    b2World(gravity.toBox2D())
{
}
