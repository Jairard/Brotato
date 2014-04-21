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
void drawAxes(FixedFramerateWindow& window);

int main(int argc, char* argv[])
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	
	Logger::enableTag("physics");

	/* World */
	Vector2f gravity(0.0f, -10.0f);
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Phy::World world(gravity, timeStep, velocityIterations, positionIterations);
	bool paused = false;

	/* Ground */
	GO::DecorBox ground(&world, Vector2f(0., -5), Vector2f(25., 10.));
	ground.setColor(sf::Color::Yellow);

	/* Objects */
	GO::Box rect(&world, Phy::Dynamic, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 1., sf::Color::Red);
	GO::Box rect2(&world, Phy::Dynamic, sf::Vector2f(0.5, sqrt(2.)), sf::Vector2f(2., 2.), Math::pi()/4., sf::Color::Blue);
	
	GO::Segment segment(&world, Phy::Static, Vector2f(-20., 20.), Vector2f(20., -20.));
	GO::Segment segment2(&world, Phy::Dynamic, Vector2f(-2., 0.), Vector2f(-2., 5.));
	segment.setColors(sf::Color::Cyan, sf::Color::Magenta);
	segment2.setColors(sf::Color::Cyan, sf::Color::Magenta);

	/* Window */
	sf::View view(sf::Vector2f(), sf::Vector2f(50., 50.));
	sf::Clock clock;
	FixedFramerateWindow window(sf::VideoMode(400, 400), "Hello Box2D");
	Graphics::DebugRenderer renderer(window);
	renderer.SetFlags(b2Draw::e_shapeBit);

	//world.setDebugRenderer(&renderer);

	window.setView(view);
	paused = true;

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
		window.render(segment2);

		drawAxes(window);
		
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

void drawAxes(FixedFramerateWindow& window)
{
	Graphics::SegmentShape xAxis(Vector2f(0., 0.), Vector2f(1., 0.)), yAxis(Vector2f(0., 0.), Vector2f(0., 1.));
	xAxis.setColor(sf::Color(255, 0, 0));
	yAxis.setColor(sf::Color(0, 255, 0));
	
	window.render(xAxis);
	window.render(yAxis);
}

