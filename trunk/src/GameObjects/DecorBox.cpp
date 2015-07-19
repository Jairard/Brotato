#include "DecorBox.hpp"

namespace GO
{
	DecorBox::DecorBox(Phy::World* world,
	                   const Pot::Vector2f& center, const Pot::Vector2f& size,
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

