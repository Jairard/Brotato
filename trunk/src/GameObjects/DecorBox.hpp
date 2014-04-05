#ifndef __GAMEOBJECTS_DECORBOX__
#define __GAMEOBJECTS_DECORBOX__

#include "Box.hpp"

namespace GO
{
	class DecorBox : public Box
	{
		public:
			DecorBox(Phy::World* world,
					 const Vector2f& center, const Vector2f& size,
					 float angle=0., const sf::Color& color=sf::Color::White);
			virtual ~DecorBox() {}
			
			virtual void setup(void);
	};
}

#endif
