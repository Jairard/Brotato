#ifndef __FIXED_FRAMERATE_WINDOW__
#define __FIXED_FRAMERATE_WINDOW__

#include <SFML/Graphics.hpp>
#include "../Graphics/Entity.hpp"

class FixedFramerateWindow : public sf::RenderWindow
{
	public:
		FixedFramerateWindow(sf::VideoMode mode, const sf::String& title, 
							 sf::Uint32 style=sf::Style::Default, 
							 const sf::ContextSettings& settings=sf::ContextSettings());

	public:
		void render(Graphics::Entity& entity, const sf::RenderStates& states=sf::RenderStates::Default);
};

#endif
