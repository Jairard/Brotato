#include <cstdio>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "render.hpp"

void handleEvents(sf::RenderWindow& window);

int main(int argc, char* argv[])
{	
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	const unsigned int width = 640, height = 480;
	const char* title = "Box2D test";

	sf::RenderWindow window(sf::VideoMode(width, height), title);
	sf::Clock clock, fpsClock;
	float settingsHz = 30., fpsRefreshTime = 0.5;
	int fps = settingsHz, frames = 0;

	//DebugRenderer renderer(window);
	//m_world->SetDebugDraw(&m_debugDraw);

	while (window.isOpen())
	{
		handleEvents(window);
		window.clear();
		window.display();

		frames++;

		float elapsed = clock.getElapsedTime().asSeconds();
		sf::Time toSleep = sf::seconds(1./settingsHz - elapsed);

		if (toSleep.asSeconds() > 0)
			sf::sleep(toSleep);
		clock.restart();

		if (fpsClock.getElapsedTime().asSeconds() > fpsRefreshTime)
		{
			fps = frames/fpsRefreshTime;
			frames = 0;
			fpsClock.restart();
		}
	}

	return EXIT_SUCCESS;
}

void handleEvents(sf::RenderWindow& window)
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
				break;
			default:
				break;
		}
	}
}
