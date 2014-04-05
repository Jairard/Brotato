#include "FixedFramerateWindow.hpp"

FixedFramerateWindow::FixedFramerateWindow(sf::VideoMode mode, const sf::String& title, 
										   sf::Uint32 style, const sf::ContextSettings& settings) :
	sf::RenderWindow(mode, title, style, settings)
{
}

void FixedFramerateWindow::render(Graphics::Entity& entity, const sf::RenderStates& states)
{
	entity.render(*this, states);
}

