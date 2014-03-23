#ifndef __SHAPE__
#define __SHAPE__

#include <SFML/Graphics.hpp>
#include "../Vector2.hpp"
#include "Entity.hpp"

namespace Graphics
{
	class Shape : public Entity
	{
		/* Methods */
		public:
			Shape(sf::PrimitiveType type, unsigned int vertexCount);
			virtual ~Shape() {}
			
			void setOrigin(const Vector2f& origin);
			void setPosition(const Vector2f& position);
			void setSize(const Vector2f& size);
			void setColor(const sf::Color& color);
			
		protected:
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
			
		/* Members */
		protected:
			sf::VertexArray m_array;
	};
}

#endif