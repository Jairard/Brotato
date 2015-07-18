#include <stdlib.h>
#include <iostream>
#include <list>

#include "PotatoPlant.hpp"

#include "../Core/Tools.hpp"
#include "../Core/Vector2.hpp"
#include "Debug/Renderer.hpp"
#include "Debug/Logger.hpp"
#include "Stem.hpp"
#include "Potato.hpp"
#include "RenderCell.hpp"
#include "RectangleGeometry.hpp"
#include "LineGeometry.hpp"

namespace Pot
{

using Debug::Logger;

const unsigned int PotatoPlant::DEFAULT_UPS = 50;
	
PotatoPlant::PotatoPlant(const sf::String& title, sf::VideoMode mode, unsigned int targetUps,
                         sf::Uint32 style, const sf::ContextSettings& settings):
	m_window(mode, title, style, settings),
	m_inputListener(m_window),
	m_stem(0),
	m_debugRenderer(new Debug::Renderer(m_window)),
	m_countingClock(),
	m_targetUps(targetUps),
	m_frameCount(0),
	m_updateCount(0),
	m_fps(0),
	m_ups(0),
	m_debugCells(false),
	m_debugPhysics(false)
{
}

void transformTest()
{
	Logger::enableTag(Logger::Warning);
	Logger::log(Logger::CWarning, "");
	
	Stem* stem = new Stem(nullptr);
	Potato* p1 = stem->instantiatePotato("potato 1");
	Potato* p11 = stem->instantiatePotato("potato 1.1");
	stem->setParent(p11, p1);
	
	//*
	p1->localTransform().setPosition(5.f, 10.f);
	p1->localTransform().setRotation(42.f);
	p1->localTransform().setScale(2.f, 1.5f);
	/*/
	p1->worldTransform().setPosition(5.f, 10.f);
	p1->worldTransform().setRotation(42.f);
	p1->worldTransform().setScale(2.f, 1.5f);
	//*/
	
	/*
	p11->worldTransform().setPosition(10.f, 5.f);
	p11->worldTransform().setRotation(100.f);
	p11->worldTransform().setScale(0.5f, 4.f);
	/*/
	p11->localTransform().setPosition(10.f, 5.f);
	p11->localTransform().setRotation(100.f);
	p11->localTransform().setScale(0.5f, 4.f);
	//*/
	
	Logger::log(Logger::CWarning, "p1 local transform");
	p1->localTransform_const().log(Logger::CWarning);
	Logger::log(Logger::CWarning, "p1 world transform");
	p1->worldTransform_const().log(Logger::CWarning);
	Logger::log(Logger::CWarning, "p2 local transform");
	p11->localTransform_const().log(Logger::CWarning);
	Logger::log(Logger::CWarning, "p2 inv local transform");
	p11->localTransform_const().inverse().log(Logger::CWarning);
	p11->parentToLocalTransform().log(Logger::CWarning);
	Logger::log(Logger::CWarning, "p2 world transform");
	p11->worldTransform_const().log(Logger::CWarning);
	Logger::log(Logger::CWarning, "p2 inv world transform");
	p11->worldTransform_const().inverse().log(Logger::CWarning);
	p11->worldToLocalTransform().log(Logger::CWarning);
	
	Vector2f p(3.456f, 7.89f);
	Vector2f r3 = p11->localToWorldTransform().transformPoint(p11->worldToLocalTransform().transformPoint(p));
	Vector2f r4 = p11->localToParentTransform().transformPoint(p11->parentToLocalTransform().transformPoint(p));
	
	Logger::log(Logger::CWarning, "World id transformation: %f, %f", r3.x, r3.y);
	Logger::log(Logger::CWarning, "Local id transformation: %f, %f", r4.x, r4.y);
	
	delete stem;
}

void PotatoPlant::initialize()
{
	Logger::enableTag("Debug");
	Logger::enableTag(Logger::Warning);
	Logger::enableTag(Logger::Error);
	//Logger::enableTag(Stem::c_tag);
	
	Logger::log(Logger::CWarning, "");
	
	m_debugRenderer->lock();
	
	m_stem = new Stem(this);
	
	Potato* p1 = m_stem->instantiatePotato("potato 1");
	Potato* p11 = m_stem->instantiatePotato("potato 1.1");
	m_stem->setParent(p11, p1);
	Potato* p12 = m_stem->instantiatePotato("potato 1.2");
	m_stem->setParent(p12, p1);
	Potato* p111 = m_stem->instantiatePotato("potato 1.1.1");
	m_stem->setParent(p111, p11);
	Potato* p112 = m_stem->instantiatePotato("potato 1.1.2");
	m_stem->setParent(p112, p11);
	Potato* p121 = m_stem->instantiatePotato("potato 1.2.1");
	m_stem->setParent(p121, p12);
	Potato* p1111 = m_stem->instantiatePotato("potato 1.1.1.1");
	m_stem->setParent(p1111, p111);
	
	//*
	setupPotato(p1);
	setupPotato(p11);
	setupPotato(p12);
	setupPotato(p111);
	setupPotato(p112);
	setupPotato(p121);
	setupPotato(p1111);
	//*/
	
	//*
	Potato* line = m_stem->instantiatePotato("line !");
	line->addCell<RenderCell>();
	LineGeometry* geometry = line->addCell<LineGeometry>();
	geometry->setPoint1(Vector2f(-50.f, -50.f));
	geometry->setPoint2(Vector2f(50.f, 50.f));
	geometry->setColor(sf::Color::Green);
	
	line->localTransform().setPosition(100.f, 250.f);
	line->localTransform().rotate(70.f);
	line->fetchCellIFP<GeometryCell>()->updateAABBs();
	//*/
	
	p1->localTransform().setPosition(100.f, 75.f);
	
	//*
	p11->localTransform().setPosition(150.f, 150.f);
	p121->localTransform().setRotation(45.f);
	p112->localTransform().setRotation(-45.f);
	//*/
	
	//*
	p1->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	p11->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	p12->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	p111->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	p112->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	p121->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	p1111->fetchCellIFP<RectangleGeometry>()->updateAABBs();
	//*/
	
	//m_stem->ensureIntegrityAsc(p121);
	
	sf::View view(sf::Vector2f(195.f, 195.f), sf::Vector2f(400.f, -400.f));
	m_window.setView(view);
	
	setCellsDebugStatus(true);
}

void PotatoPlant::setupPotato(Potato* potato)
{
	potato->addCell<RenderCell>();
	RectangleGeometry* geometry =  potato->addCell<RectangleGeometry>();
	geometry->setSize(Vector2f(100.f, 50.f));
	geometry->setColor(sf::Color::Green);
}

void PotatoPlant::shutdown()
{
	delete m_stem;
	delete m_debugRenderer;
}

int PotatoPlant::loop()
{
	initialize();
	
	sf::Clock clock;
	sf::Time previous;
	const float updateFramerate = 1. / (float)m_targetUps;
	float acc = 0.;
	
	m_countingClock.restart();
	
	while (m_window.isOpen())
	{
		sf::Time current = clock.getElapsedTime();
		acc += (current - previous).asSeconds();
		previous = current;
		
		try
		{
			handleInput();
			
			while (acc >= updateFramerate)
			{
				update();
				m_updateCount++;
				acc -= updateFramerate;
			}
			
			render(acc / updateFramerate);
			m_frameCount++;
		}
		catch (std::exception& e)
		{
			Logger::log(Logger::CError, "An exception occured: %s", e.what());
			m_window.close();
			shutdown();
			return EXIT_FAILURE;
		}
		
		checkTime();
	}
	
	shutdown();
	return EXIT_SUCCESS;
}

void PotatoPlant::handleInput()
{
	sf::Event event;
	
	while (m_window.pollEvent(event))
		m_inputListener.onEvent(event);
}

void PotatoPlant::render(float elapsedTime)
{
	// clear() & display() in Stem::render() ?
	m_window.clear();
	m_stem->render(elapsedTime);
	
	if (m_debugCells)
	{
		m_debugRenderer->unlock();
		m_stem->debugRender(*m_debugRenderer);
		m_debugRenderer->lock();
	}
	
	if (m_debugPhysics)
		;// TODO: physics debug render
	
	m_window.display();
}

void PotatoPlant::update()
{
	m_stem->update();
}

void PotatoPlant::checkTime()
{
	if (m_countingClock.getElapsedTime().asSeconds() >= 1.)
	{
		m_fps = m_frameCount;
		m_ups = m_updateCount;
		m_frameCount = m_updateCount = 0;
		m_countingClock.restart();
		
		Logger::log("Debug", "%d fps - %d updates", m_fps, m_ups);
	}
}

}
