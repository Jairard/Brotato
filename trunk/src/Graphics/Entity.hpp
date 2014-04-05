#ifndef __GRAPHICS_ENTITY__
#define __GRAPHICS_ENTITY__

#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Entity
	{
		public:
			Entity();
			virtual ~Entity() {}
			
			virtual void render(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}

#endif

