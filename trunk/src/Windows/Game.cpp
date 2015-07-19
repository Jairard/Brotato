#include "Window.hpp"
#include "Game.hpp"
#include "../GameObjects.hpp"
#include "../PotatoEngine/Core/Math.hpp"
#include "../PotatoEngine/Debug/Logger.hpp"
#include "../Graphics/DebugRenderer.hpp"

Game::Game(Window& window, Phy::World* world):
	m_world(world),
	m_inputListener(0),
	m_renderer(0)
{
	m_inputListener = new Pot::SimpleInputListener(window);
	m_renderer = new Graphics::Renderer(window);
	
	Graphics::DebugRenderer* debugRenderer = new Graphics::DebugRenderer(window);
	m_world->setDebugRenderer(debugRenderer);
	
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
	GO::DecorBox* ground = new GO::DecorBox(m_world, Pot::Vector2f(0., -5), Pot::Vector2f(25., 10.));
	ground->setColor(sf::Color::Yellow);

	/* Objects */
	GO::Box* rect = new GO::Box(m_world, Phy::Dynamic, Pot::Vector2f(0., 20.), Pot::Vector2f(2., 2.), 1., sf::Color::Red);
	GO::Box* rect2 = new GO::Box(m_world, Phy::Dynamic, Pot::Vector2f(0.5, sqrt(2.)), Pot::Vector2f(2., 2.), Pot::Math::pi()/4., sf::Color::Blue);
	
	GO::Segment* segment = new GO::Segment(m_world, Phy::Static, Pot::Vector2f(-20., 20.), Pot::Vector2f(20., -20.));
	GO::Segment* segment2 = new GO::Segment(m_world, Phy::Dynamic, Pot::Vector2f(-2., 0.), Pot::Vector2f(-2., 5.));
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
	GO::Box* rect = new GO::Box(m_world, Phy::Dynamic, Pot::Vector2f(0., 20.), Pot::Vector2f(2., 2.), 0., sf::Color::Red);
	m_renderer->addEntity(rect);
	
	Pot::Debug::Logger::enableTag("graphics");
}

void Game::initScene3()
{
	GameObject go("test");
	Graphics::GeometryComponent* geometry = new Graphics::GeometryComponent(sf::Quads, 4);
	DummyComponent* dummy = new DummyComponent();
	Graphics::DummyGeo* dummyGeo = new Graphics::DummyGeo(sf::Quads, 4);
	//Graphics::RenderComponent* renderer = new Graphics::RenderComponent(window);
	
	go.addComponent(geometry);
	go.addComponent(dummy);
	go.addComponent(dummyGeo);
	//go.addComponent(renderer);
}

void Game::handleInput(const sf::Event& event)
{
	if (m_inputListener != 0)
		m_inputListener->onEvent(event);
}

void Game::updateLogics()
{
	m_renderer->m_window.clear();
	m_world->step();
	m_renderer->m_window.display();
}

void Game::render(float coef)
{
	UNUSED(coef);
	/*
	if (m_renderer != 0)
		m_renderer->render(coef);
	//*/
}

