#include "DecorBox.hpp"

namespace GO
{
	DecorBox::DecorBox(Phy::World* world,
					   const Vector2f& center, const Vector2f& size,
					   float angle, const sf::Color& color) :
		Box(world, Phy::Static, center, size, angle, color)
	{
	}
	
	void DecorBox::setup()
	{
		fixtureDef().density = 0.;
		Box::setup();
	}
}

