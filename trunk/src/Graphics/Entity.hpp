#ifndef __ENTITY__
#define __ENTITY__

#include <SFML/Graphics.hpp>

namespace Graphics
{
	class Entity: public sf::Drawable
	{
		public:
			Entity();
			
			virtual void draw (sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}

#endif

