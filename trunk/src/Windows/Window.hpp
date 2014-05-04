#ifndef __WINDOWS_WINDOW__
#define __WINDOWS_WINDOW__

#include <list>
#include <SFML/Graphics.hpp>
#include "../Graphics/Entity.hpp"
#include "../Graphics/Renderer.hpp"

class WindowUpdater;
class InputListener;
class Game;

class Window: public sf::RenderWindow
{
	public:
		Window(sf::VideoMode mode, const sf::String& title, 
		       sf::Uint32 style=sf::Style::Default, 
		       const sf::ContextSettings& settings=sf::ContextSettings());
		~Window();
		
		void setGame(Game* game);
		int fps(void) const  { return m_fps; }
		int ups(void) const  { return m_ups; }
		
		void loop(void);
		void render(Graphics::Entity& entity, const sf::RenderStates& states=sf::RenderStates::Default);
		
	protected:
		Game* m_game;
		sf::Clock m_countingClock;
		unsigned int m_frameCount, m_updateCount;
		unsigned int m_fps, m_ups;
		
		void handleInput(void);
		void updateGame(void);
		void render(float coef);
		void checkTime(void);
};

#endif
