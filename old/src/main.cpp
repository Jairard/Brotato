#include <SFML/Graphics.hpp>
/*
#include <Box2D/Box2D.h>
#include <cstdio>
#include <stdlib.h>
//#include <iostream>

/*
#include "boxTest.h"
#include "phyWorld.h"
#include "phyRectangle.h"
#include "phyLine.h"
#include "vector2.h"

#include "lineShape.h"
*/

/*
using namespace std;

void testSFML16();
void testBox2D(void);
void testSFML(void);
void test2(void);
void testLine(void);
*/

int main()
{
	/*
	PhyWorld world;
	world.setScale(60);
	sf::Transform t = world.getTransform();
	Vector2f p(1, 1);
	p = t.transformPoint(p);
	std::cout << p << std::endl;
	return EXIT_SUCCESS;
	//*/

    //testBox2D();
    //testSFML();
    //boxTest();
	//test2();
	//testLine();

	return EXIT_SUCCESS;
}

void testBox2D()
{
    /*
    // Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

    // Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world->
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.
    */
}

void testSFML()
{
    /*
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::Clock clock;
	sf::Uint32 delay = 1000./60;

    PhyRectangle shape(0, sf::Vector2f(100, 100), sf::Vector2f(50, 50), sf::Color::Green);

	while (window.isOpen())
	{
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		shape.rotate(1);

		window.clear();
		window.draw(shape);
		window.display();

		sf::Uint32 elapsed = clock.getElapsedTime().asMilliseconds();
		if (elapsed < delay)
			sf::sleep(sf::milliseconds(delay - elapsed));
	}
    */
}

void test2()
{
    /*
    PhyWorld* world = new PhyWorld();
    world->SetGravity(b2Vec2(0., -9.81));
	PhyRectangle rect(world, sf::Vector2f(1., 1.), sf::Vector2f(.1, .1), sf::Color::White, b2_dynamicBody);
	rect.body()->SetGravityScale(0.01);
    sf::Vector2f p1(5., 5.), p2(7.5f, 7.5f);
	cout << "Init OK" << endl;

	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	sf::Clock clock;
	sf::Uint32 delay = 1000./60;

	while (window.isOpen())
	{
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		world->Step();

        window.clear();
		window.draw(rect);
		window.display();

		sf::Uint32 elapsed = clock.getElapsedTime().asMilliseconds();
		if (elapsed < delay)
			sf::sleep(sf::milliseconds(delay - elapsed));
	}

	delete world;
    */
}

void testLine()
{
    /*
	PhyWorld* world = new PhyWorld();
	//world->setScale(.5);

	sf::RenderWindow window(sf::VideoMode(600, 600), "Line test");
	float thickness = 5.;
	Vector2f p1(300, 300), p2(400, 400);
	/*
	LineShape line(p1, p2, thickness);
	/*/
    //PhyLine line(world, p1, p2);
    //*/
    /*

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//*
			if (event.type == sf::Event::MouseMoved)
				line.setSecondPoint(event.mouseMove.x, event.mouseMove.y);
			if (event.type == sf::Event::MouseWheelMoved)
			{
				if (event.mouseWheel.delta > 0)
					thickness += 2.;
				else if (event.mouseWheel.delta < 0)
					thickness -= 2.;

				if (thickness > 100.)
					thickness = 100;
				if (thickness < 1.)
					thickness = 1.;
				line.setThickness(thickness);
			}
			//*/
    /*
		}

		window.clear();
		window.draw(line);
		window.display();
	}

	delete world;
    */
}
