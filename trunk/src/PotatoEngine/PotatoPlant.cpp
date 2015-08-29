#include <stdlib.h>
#include <iostream>
#include <list>

#include "PotatoPlant.hpp"

#include "Core/Tools.hpp"
#include "Core/Vector2.hpp"
#include "Debug/Renderer.hpp"
#include "Debug/Logger.hpp"
#include "Stem.hpp"
#include "PotatoDNA.hpp"
#include "RenderCell.hpp"
#include "RectangleGeometry.hpp"
#include "LineGeometry.hpp"

namespace Pot
{
	using Debug::Logger;

	namespace
	{
		FUNUSED(void transformTest());
		FUNUSED(void setupPotato(Potato* potato));
		FUNUSED(Stem* initScene1(PotatoPlant* plant, sf::RenderWindow& window));
		FUNUSED(void potataDNATest());

		void transformTest()
		{
			Logger::enableTag(Logger::Warning);
			Logger::log(Logger::CWarning, "");

			Stem* stem = new Stem(nullptr);
			PotatoDNA p1 = stem->instantiatePotato("potato 1");
			PotatoDNA p11 = stem->instantiatePotato("potato 1.1");
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
			p1->localTransform().log(Logger::CWarning);
			Logger::log(Logger::CWarning, "p1 world transform");
			p1->worldTransform().log(Logger::CWarning);
			Logger::log(Logger::CWarning, "p2 local transform");
			p11->localTransform().log(Logger::CWarning);
			Logger::log(Logger::CWarning, "p2 inv local transform");
			p11->localTransform().inverse().log(Logger::CWarning);
			p11->parentToLocalTransform().log(Logger::CWarning);
			Logger::log(Logger::CWarning, "p2 world transform");
			p11->worldTransform().log(Logger::CWarning);
			Logger::log(Logger::CWarning, "p2 inv world transform");
			p11->worldTransform().inverse().log(Logger::CWarning);
			p11->worldToLocalTransform().log(Logger::CWarning);

			Vector2f p(3.456f, 7.89f);
			Vector2f r3 = p11->localToWorldTransform().transformPoint(p11->worldToLocalTransform().transformPoint(p));
			Vector2f r4 = p11->localToParentTransform().transformPoint(p11->parentToLocalTransform().transformPoint(p));

			Logger::log(Logger::CWarning, "World id transformation: %f, %f", r3.x, r3.y);
			Logger::log(Logger::CWarning, "Local id transformation: %f, %f", r4.x, r4.y);

			delete stem;
		}

		void setupPotato(PotatoDNA potato)
		{
			potato->addCell<RenderCell>();
			RectangleGeometry* geometry =  potato->addCell<RectangleGeometry>();
			geometry->setSize(Vector2f(100.f, 50.f));
			geometry->setColor(sf::Color::Green);
		}

		Stem* initScene1(PotatoPlant* plant, sf::RenderWindow& window)
		{
			Stem* stem = new Stem(plant);

			PotatoDNA p1 = stem->instantiatePotato("potato 1");
			PotatoDNA p11 = stem->instantiatePotato("potato 1.1");
			stem->setParent(p11, p1);
			PotatoDNA p12 = stem->instantiatePotato("potato 1.2");
			stem->setParent(p12, p1);
			PotatoDNA p111 = stem->instantiatePotato("potato 1.1.1");
			stem->setParent(p111, p11);
			PotatoDNA p112 = stem->instantiatePotato("potato 1.1.2");
			stem->setParent(p112, p11);
			PotatoDNA p121 = stem->instantiatePotato("potato 1.2.1");
			stem->setParent(p121, p12);
			PotatoDNA p1111 = stem->instantiatePotato("potato 1.1.1.1");
			stem->setParent(p1111, p111);

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
			PotatoDNA line = stem->instantiatePotato("line !");
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

			//stem->ensureIntegrityAsc(p121);

			sf::View view(sf::Vector2f(195.f, 195.f), sf::Vector2f(400.f, -400.f));
			window.setView(view);

			plant->setCellsDebugStatus(true);
			return stem;
		}

		void potataDNATest()
		{
			Logger::log(Logger::CWarning, "DNA size: %d", sizeof(PotatoDNA));

			Stem* stem = new Stem(nullptr);
			PotatoDNA dna(stem->instantiatePotato("p2"));
		}
	}

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

void PotatoPlant::initialize()
{
	Logger::enableTag("Debug");
	Logger::enableTag(Logger::Assert);
	Logger::enableTag(Logger::Warning);
	Logger::enableTag(Logger::Error);
	//Logger::enableTag(Stem::c_tag);
	
	Logger::log(Logger::CWarning, "");
	
	m_debugRenderer->lock();
	
	m_stem = initScene1(this, m_window);
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
