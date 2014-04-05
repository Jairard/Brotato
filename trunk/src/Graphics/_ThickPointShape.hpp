#ifndef __GRAPHICS_THICKPONT_SHAPE__
#define __GRAPHICS_THICKPONT_SHAPE__

#include <SFML/Graphics.hpp>

class ThickPointShape: public sf::RectangleShape
{
	public:
		ThickPointShape(const sf::RenderWindow* window, const sf::Vector2f center=sf::Vector2f());
		~ThickPointShape() {}

		void setThickness(float thickness);
		void setColor(const sf::Color& color);

	protected:
		float _thickness;
		const sf::RenderWindow* _window;

	private:
		void update(void);
};

#endif
