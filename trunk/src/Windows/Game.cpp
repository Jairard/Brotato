#include "Window.hpp"
#include "Game.hpp"
#include "../GameObjects.hpp"
#include "../Core/Math.hpp"
#include "../Core/Logger.hpp"

Game::Game(Window& window, Phy::World* world):
	m_world(world),
	m_inputListener(0),
	m_renderer(0)
{
	m_inputListener = new InputListener(window);
	m_renderer = new Graphics::Renderer(window);
	
	initScene1();
}

Game::~Game()
{
	if (m_inputListener != 0)
		delete m_inputListener;
	
	if (m_renderer != 0)
		delete m_renderer;
}

void Game::initScene1()
{
	/* Ground */
	GO::DecorBox* ground = new GO::DecorBox(m_world, Vector2f(0., -5), Vector2f(25., 10.));
	ground->setColor(sf::Color::Yellow);

	/* Objects */
	GO::Box* rect = new GO::Box(m_world, Phy::Dynamic, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 1., sf::Color::Red);
	GO::Box* rect2 = new GO::Box(m_world, Phy::Dynamic, sf::Vector2f(0.5, sqrt(2.)), sf::Vector2f(2., 2.), Math::pi()/4., sf::Color::Blue);
	
	GO::Segment* segment = new GO::Segment(m_world, Phy::Static, Vector2f(-20., 20.), Vector2f(20., -20.));
	GO::Segment* segment2 = new GO::Segment(m_world, Phy::Dynamic, Vector2f(-2., 0.), Vector2f(-2., 5.));
	segment->setColors(sf::Color::Cyan, sf::Color::Magenta);
	segment2->setColors(sf::Color::Cyan, sf::Color::Magenta);
	
	m_renderer->addEntity(ground);
	m_renderer->addEntity(rect);
	m_renderer->addEntity(rect2);
	m_renderer->addEntity(segment);
	m_renderer->addEntity(segment2);
}

void Game::initScene2()
{
	GO::Box* rect = new GO::Box(m_world, Phy::Dynamic, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 0., sf::Color::Red);
	m_renderer->addEntity(rect);
	
	Logger::enableTag("graphics");
}

void Game::handleInput(const sf::Event& event)
{
	if (m_inputListener != 0)
		m_inputListener->onEvent(event);
}

void Game::updateLogics()
{
	m_world->step();
}

void Game::render(float coef)
{
	if (m_renderer != 0)
		m_renderer->render(coef);
}

