#include <cstdio>
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Window.hpp"
#include "Core.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	Logger::enableTag("window");
	
	/* Window */
	sf::View view(sf::Vector2f(), sf::Vector2f(50., -50.));
	Window window(sf::VideoMode(400, 400), "Window test");
	
	/* World */
	Vector2f gravity(0.0f, -10.0f);
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Phy::World world(gravity, timeStep, velocityIterations, positionIterations);
	Game* game = new Game(window, &world);
	
	window.setView(view);
	window.setGame(game);
	window.loop();
}

