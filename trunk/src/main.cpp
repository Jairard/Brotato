#include <cstdio>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "render.hpp"
#include "rectangleShape.hpp"
#include "vector2.hpp"

void handleEvents(sf::RenderWindow& window);
void helloBox2D(void);

int main(int argc, char* argv[])
{	
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	helloBox2D();
	return EXIT_SUCCESS;

	/*
	const unsigned int width = 640, height = 480;
	const char* title = "Box2D test";

	sf::RenderWindow window(sf::VideoMode(width, height), title);
	sf::Clock clock, fpsClock;
	float settingsHz = 30., fpsRefreshTime = 0.5;
	int fps = settingsHz, frames = 0;

	b2World world(Vector2f(0., 9.81).toBox2D());
	DebugRenderer renderer(window);
	world.SetDebugDraw(&renderer);

	while (window.isOpen())
	{
		handleEvents(window);
		window.clear();
		window.display();

		frames++;

		world.Step(1./settingsHz, 5, 5);

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
	//*/
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

void helloBox2D()
{
	/* World */
	Vector2f gravity(0.0f, -10.0f);
	b2World world(gravity.toBox2D());

	/* Ground */
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	/* Box */
	RectangleShape rect2(&world, sf::Vector2f(0.5, 1.), sf::Vector2f(2., 2.), 0., sf::Color::Blue, b2_dynamicBody);
	RectangleShape rect(&world, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 1., sf::Color::Red, b2_dynamicBody);
	/*
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 20.0f);
	bodyDef.angle = 1.;
	b2Body* body = world.CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
	*/

	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	//sf::RectangleShape rect(sf::Vector2f(2., 2.));
	//rect.setOrigin(1., 1.);
	sf::View view(sf::Vector2f(), sf::Vector2f(50., 50.));
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Hello Box2D");
	DebugRenderer renderer(window);

	world.SetDebugDraw(&renderer);
	renderer.SetFlags(b2Draw::e_shapeBit);

	window.setView(view);

	while (window.isOpen())
	{
		handleEvents(window);
		window.clear();

		world.Step(timeStep, velocityIterations, positionIterations);
		//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		//world.DrawDebugData();
		rect.update();
		rect2.update();

		window.draw(rect);
		window.draw(rect2);

		window.display();

		float elapsed = clock.getElapsedTime().asSeconds();
		sf::Time toSleep = sf::seconds(timeStep - elapsed);

		if (toSleep.asSeconds() > 0)
			sf::sleep(toSleep);
		clock.restart();
	}
}
