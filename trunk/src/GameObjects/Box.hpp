#ifndef __GAMEOBJECTS_BASEBOX__
#define __GAMEOBJECTS_BASEBOX__

#include "../Vector2.hpp"
#include "GameObject.hpp"
#include "../Physics/World.hpp"
#include "../Physics/Rectangle.hpp"
#include "../Graphics/RectangleShape.hpp"

namespace GO
{
	class Box : public GameObject, public Phy::Rectangle, public Graphics::RectangleShape
	{
		public:
			Box(Phy::World* world, Phy::BodyType type,
					const Vector2f& center, const Vector2f& size,
					float angle=0., const sf::Color& color=sf::Color::White);
			virtual ~Box() {}
	
			virtual void update(const Vector2f& position, float angle);
			//virtual void setup(void);
	};
}

#endif
