#ifndef __SHAPE__
#define __SHAPE__

#include <SFML/Graphics.hpp>
#include "../Core/Vector2_.hpp"
#include "SFMLEntity.hpp"

namespace Graphics
{
	class Shape : public SFMLEntity
	{
		/* Methods */
		public:
			Shape(sf::PrimitiveType type, unsigned int vertexCount);
			virtual ~Shape() {}

			void setColor(const sf::Color& color);

		protected:
			virtual void render(sf::RenderTarget& target, float coef, sf::RenderStates states);
			virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		/* Members */
		protected:
			sf::VertexArray m_array;
	};
}

#endif
