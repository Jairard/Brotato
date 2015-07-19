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
			
			virtual void setOrigin(const Pot::Vector2f& origin);
			virtual void setPosition(const Pot::Vector2f& position);
			virtual void setScale(const Pot::Vector2f& factors);
			virtual void setRotation(float angle);
			
			virtual void onGameUpdate(const Pot::Vector2f& position, float angle);
	};
}

#endif

