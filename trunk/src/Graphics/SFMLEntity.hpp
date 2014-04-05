#ifndef __GRAPHICS_SFML_ENTITY__
#define __GRAPHICS_SFML_ENTITY__

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

namespace Graphics
{
	class SFMLEntity: public sf::Drawable, public sf::Transformable, public Entity
	{
		public:
			SFMLEntity();
			virtual ~SFMLEntity() {}

		protected:
			virtual void render(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}

#endif

