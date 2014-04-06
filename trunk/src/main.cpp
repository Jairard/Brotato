#include <cstdio>
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Windows/FixedFramerateWindow.hpp"
#include "Core.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"
#include "GameObjects.hpp"

void handleEvents(sf::RenderWindow& window, bool* paused);
void drawGrid(FixedFramerateWindow& window);

int main(int argc, char* argv[])
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	Logger::enableTag("C variadic log");
	Logger::enableTag("C err log");
	
	Logger::log("C variadic log", "loggy log %d %s", 12, "proute");
	Logger::log(std::cerr, "C err log", "LOL !!!!%c!", '1');
	Logger::log(std::string("C++ log"), std::string("XD"));
	Logger::log(std::cerr, std::string("C++ err log"), std::string("SWAG"));
	Logger::log(std::string("Another C++ log"), "XD");
	Logger::log("Random log", "XD");
	Logger::log(Logger::Warning, "Achtung !");

	/* World */
	Vector2f gravity(0.0f, -10.0f);
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Phy::World world(gravity, timeStep, velocityIterations, positionIterations);
	bool paused = false;

	/* Ground */
	GO::DecorBox ground(&world, Vector2f(0., -5.), Vector2f(25., 10.));
	ground.setColor(sf::Color::Green);

	/* Boxes */
	GO::Box rect(&world, Phy::Dynamic, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 1., sf::Color::Red);
	GO::Box rect2(&world, Phy::Dynamic, sf::Vector2f(0.5, sqrt(2.)), sf::Vector2f(2., 2.), Math::pi()/4., sf::Color::Blue);
	
	Graphics::SegmentShape segment(Vector2f(-20., -20.), Vector2f(20., 20.));
	segment.setColors(sf::Color::Yellow, sf::Color::Magenta);
	
	Graphics::PointShape p1(Vector2f(-10., 10.)), p2(Vector2f(10., -10.));
	p1.setColor(sf::Color::Green);
	p2.setColor(sf::Color::Cyan);
	
	Graphics::RectangleShape rectangle(Vector2f(10., -10.), Vector2f(2., 2.));
	rectangle.setColor(sf::Color::Yellow);

	sf::View view(sf::Vector2f(), sf::Vector2f(50., 50.));
	sf::Clock clock;
	FixedFramerateWindow window(sf::VideoMode(400, 400), "Hello Box2D");
	Graphics::DebugRenderer renderer(window);

	//world.setDebugRenderer(&renderer);
	renderer.SetFlags(b2Draw::e_shapeBit);

	window.setView(view);

	while (window.isOpen())
	{
		handleEvents(window, &paused);
		window.clear();

		if (!paused)
			world.step();
		drawGrid(window);

		window.render(ground);
		window.render(rect);
		window.render(rect2);
		window.render(segment);
		window.render(rectangle);
		window.render(p1);
		window.render(p2);

		window.display();

		float elapsed = clock.getElapsedTime().asSeconds();
		sf::Time toSleep = sf::seconds(timeStep - elapsed);

		if (toSleep.asSeconds() > 0)
			sf::sleep(toSleep);
		clock.restart();
	}
}

void handleEvents(sf::RenderWindow& window, bool* paused)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				else if (event.key.code == sf::Keyboard::P)
					*paused = !(*paused);
				break;
			default:
				break;
		}
	}
}

void drawGrid(FixedFramerateWindow& window)
{
	sf::View view = window.getView();
	Vector2f center = view.getCenter(), size = view.getSize();
	int minX = (int)ceil(center.x - size.x/2.), maxX = (int)floor(center.x + size.x/2.);
	int minY = (int)ceil(center.y - size.y/2.), maxY = (int)floor(center.y + size.y/2.);
	
	for (int x=minX; x <=maxX; x++)
	{
		for (int y=minY; y<maxY; y++)
		{
			Graphics::PointShape point(Vector2f(x, y));
			point.setColor(sf::Color::White);
			window.render(point);
		}
	}
}

