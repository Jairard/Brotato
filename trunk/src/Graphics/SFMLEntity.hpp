#ifndef __GRAPHICS_SFML_ENTITY__
#define __GRAPHICS_SFML_ENTITY__

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "../Core/Vector2.hpp"

namespace Graphics
{
	class SFMLEntity: public sf::Drawable, public sf::Transformable, public Entity
	{
		public:
			SFMLEntity();
			virtual ~SFMLEntity() {}
			
			virtual void setOrigin(const Vector2f& origin);
			virtual void setPosition(const Vector2f& position);
			virtual void setScale(const Vector2f& factors);
			virtual void setRotation(float angle);
			
			virtual void onGameUpdate(const Vector2f& position, float angle);
	};
}

#endif

