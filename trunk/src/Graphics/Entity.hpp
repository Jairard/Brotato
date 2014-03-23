#ifndef __GRAPHICS_ENTITY__
#define __GRAPHICS_ENTITY__

#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Entity: public sf::Drawable, public sf::Transformable
	{
		public:
			Entity();
			virtual ~Entity() {}
			
		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}

#endif

