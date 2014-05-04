#ifndef __GRAPHICS_ENTITY__
#define __GRAPHICS_ENTITY__

#include <SFML/Graphics.hpp>
#include "../Core/Vector2.hpp"

namespace Graphics
{
	class Entity
	{
		public:
			Entity();
			virtual ~Entity() {}
			
			virtual void setPosition(const Vector2f& position);
			virtual void setRotation(float angle);
			
			virtual void onGameUpdate(const Vector2f& position, float angle);
			virtual void render(sf::RenderTarget& target, float coef, sf::RenderStates states=sf::RenderStates::Default);
			
		protected:
			Vector2f m_velocity, m_lastPosition, m_currentPosition;
			float m_angularVelocity, m_lastRotation, m_currentRotation;
			
			virtual void extrapolate(float coef);
	};
}

#endif

