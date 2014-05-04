#include "InputListener.hpp"
#include "Game.hpp"
#include "Window.hpp"

#include "../Core/Logger.hpp"

Window::Window(sf::VideoMode mode, const sf::String& title, 
               sf::Uint32 style, const sf::ContextSettings& settings) :
	sf::RenderWindow(mode, title, style, settings),
	m_game(0),
	m_countingClock(),
	m_frameCount(0),
	m_updateCount(0),
	m_fps(0),
	m_ups(0)
{}

Window::~Window()
{
	if (m_game != 0)
		delete m_game;
}

void Window::setGame(Game* game)
{
	if (m_game != 0)
		delete m_game;
	m_game = game;
}

void Window::loop()
{
	sf::Clock clock;
	sf::Time previous;
	float updateFramerate = (m_game != 0 ? m_game->framerate() : 1./60.);
	float acc = updateFramerate;
	
	m_frameCount = m_updateCount = 0;
	m_countingClock.restart();
			
	while (isOpen())
	{
		sf::Time current = clock.getElapsedTime();
		acc += (current - previous).asSeconds();
		previous = current;
		
		handleInput();
		while (acc >= updateFramerate)
		{
			updateGame();
			acc -= updateFramerate;
		}
		render(acc / updateFramerate);
		
		checkTime();
	}
}

void Window::handleInput()
{
	sf::Event event;
	
	while (pollEvent(event))
		if (m_game != 0)
			m_game->handleInput(event);
}

void Window::updateGame()
{
	Logger::log("update", "updating game logics");
	if (m_game != 0)
		m_game->updateLogics();
	m_updateCount++;
}

void Window::render(float coef)
{
	Logger::log("update", "rendering %lf", coef);
	if (m_game != 0)
		m_game->render(coef);
	m_frameCount++;
}

void Window::checkTime(void)
{
	if (m_countingClock.getElapsedTime().asSeconds() >= 1.)
	{
		m_fps = m_frameCount;
		m_ups = m_updateCount;
		m_frameCount = m_updateCount = 0;
		m_countingClock.restart();
		
		Logger::log("window", "%d fps - %d updates", m_fps, m_ups);
	}
}

void Window::render(Graphics::Entity& entity, const sf::RenderStates& states)
{
	entity.render(*this, 0., states);
}

