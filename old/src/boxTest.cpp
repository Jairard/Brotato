#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <time.h>
#include <math.h>

#include "phyworld.h"
#include "phyRectangle.h"
#include "interpolationWindow.h"
#include "boxTest.h"

class WindowTest: public InterpolationWindow
{
	public:
		WindowTest(PhyWorld* world, const sf::ContextSettings& settings):
			InterpolationWindow(sf::VideoMode(600, 600), "Proute", sf::Style::Default, settings, 4),
			_rect(world, Vector2f(20.0, 60.0), Vector2f(10.0, 10.0), sf::Color::Red, b2_dynamicBody),
			_rect2(world, Vector2f(30.0, 60.0), Vector2f(10.0, 10.0), sf::Color::Blue, b2_dynamicBody),
			_world(world),
			_clock()
		{
			_world->setScale(5.);
			_world->rotate(-10);
			std::cout << _world->timeStep() << std::endl;
			addInterpolable(&_rect);
			addInterpolable(&_rect2);
			_rect.body()->SetAngularVelocity(10*M_PI);
			_rect2.body()->SetAngularVelocity(-10*M_PI);
		}

		void onEvent(const sf::Event& event)
		{
			std::stringstream str;
			str << fps() << " fps";
			setTitle(str.str());
		}

		void onUpdate()
		{
			_world->Step();
			std::cout << _world->getScale() << std::endl;
			if (_rect.body()->GetPosition().y < 0)
				std::cout << "end : " << _clock.getElapsedTime().asSeconds() << std::endl;
		}

		void onDraw()
		{
			//std::cout << Vector2f(_rect.body()->GetPosition()) << " " << Vector2f(_rect.getPosition()) << std::endl;
			draw(_rect2);
			draw(_rect);
		}

	private:
		PhyWorld* _world;
		PhyRectangle _rect, _rect2;
		sf::Clock _clock;
};

void boxTest()
{
	srand(time(0));

	/**************************/
	/*  Initializing physics  */
	/**************************/

	/* World */
	PhyWorld* world = new PhyWorld();
	/*
	world->setScale(45);
	world->setOrigin(Vector2f(5, 5));
	world->setPosition(300, 300);
	//*/

	/* Border */
	sf::RectangleShape background(sf::Vector2f(600, 600));
	background.setFillColor(sf::Color(127, 127, 127));
	PhyRectangle down(world, sf::Vector2f(5., 9.5), sf::Vector2f(9.025, 0.02), sf::Color::Black);
	PhyRectangle up(world, sf::Vector2f(5., 0.5), sf::Vector2f(9.025, 0.02), sf::Color::Black);
	PhyRectangle left(world, sf::Vector2f(0.5, 5.), sf::Vector2f(0.02, 9.025), sf::Color::Black);
	PhyRectangle right(world, sf::Vector2f(9.5, 5.), sf::Vector2f(0.02, 9.025), sf::Color::Black);

	/* Boxes */
	PhyRectangle* boxes[BOX_COUNT];
	double angularVelocity[BOX_COUNT];

	for (int i=0; i<BOX_COUNT; i++)
	{
		angularVelocity[i] = between(-MAX_ANGULAR_VELOCITY, MAX_ANGULAR_VELOCITY);
		sf::Color color(between(0, 255), between(0, 255), between(0, 255));
		/*
		double x = between(1+BOX_SIZE, 9-BOX_SIZE), y = between(1+BOX_SIZE, 9-BOX_SIZE);
		boxes[i] = new PhyRectangle(sf::FloatRect(x, y, BOX_SIZE, BOX_SIZE), color, b2_dynamicBody);
		/*/
		//double cx = between(1+BOX_SIZE/2, 9-BOX_SIZE/2), cy = between(1+BOX_SIZE/2, 9-BOX_SIZE/2);
		double cx = between(1+MARGIN, 9-MARGIN), cy = between(1+MARGIN, 9-MARGIN);
		boxes[i] = new PhyRectangle(world, sf::Vector2f(cx, cy), sf::Vector2f(BOX_SIZE, BOX_SIZE), color, b2_dynamicBody);
		//boxes[i]->body()->SetGravityScale(0.0);
		//*//*
		boxes[i]->body()->SetAngularVelocity(angularVelocity[i]);
	}

	/*************/
	/*  Looping  */
	/*************/

	//sf::RenderWindow proute;
	//InterpolationWindow proute2(sf::VideoMode(600, 600), "Box2D simulation with SFML");
	sf::ContextSettings settings;
	//settings.antialiasingLevel = 8;
	PhyWorld test;
	test.setScale(10);
	test.setTimeStep(.5);
	test.SetGravity(b2Vec2(0, -9.81));
	WindowTest window(&test, settings);
	Vector2f center(300, 300), current = world->screenVector(world->GetGravity());
	sf::Uint32 fps = 30;
	int wheelCount = 0;
	sf::Uint32 delay = (1./fps) * 1000;
	sf::Clock clock;

	window.loop();
	return;

	while (window.isOpen())
	{
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				current = Vector2f(event.mouseButton.x, event.mouseButton.y);
				Vector2f gravity = world->phyVector(current-center);
				world->SetGravity(gravity.toPhy());
			}
			if (event.type == sf::Event::MouseButtonReleased)
				std::cout << "released" << std::endl;
			if (event.type == sf::Event::MouseWheelMoved)
			{
				wheelCount += event.mouseWheel.delta;
				if (wheelCount < 0)
					wheelCount = 0;
				if (wheelCount > 10)
					wheelCount = 10;
				std::cout << "wheel delta : " << event.mouseWheel.delta << std::endl;
				std::cout << "wheelCount : " << wheelCount << std::endl;
				for (int i=0; i<BOX_COUNT; i++)
					boxes[i]->body()->SetAngularVelocity(wheelCount/10. * angularVelocity[i]);
			}
		}

		Vector2f gravity(world->GetGravity());
		sf::Transform t;
		t.rotate(-1);
		gravity = t.transformPoint(gravity);
		world->SetGravity(gravity.toPhy());

		world->Step();
		world->rotate(1);
		//b2Vec2 position = box.body()->GetPosition();
		//std::cout << position.x << " " << position.y <<  " " << box.body()->GetAngle() << std::endl;

		window.clear();

		window.draw(background);
		window.draw(down);
		window.draw(up);
		window.draw(left);
		window.draw(right);
		for (int i=0; i<BOX_COUNT; i++)
			window.draw(*boxes[i]);

		window.display();

		sf::Uint32 	elapsed = clock.getElapsedTime().asMilliseconds();
		if (elapsed < delay)
			sf::sleep(sf::milliseconds(delay - elapsed));

		std::stringstream str;
		str << "Box2D simulation with SFML - " << elapsed << " ms/frame";
		window.setTitle(str.str());
	}

	for (int i=0; i<BOX_COUNT; i++)
		delete boxes[i];
	delete world;
}

double between(double min, double max)
{
	double r = rand() / (double)RAND_MAX;
	return min + r*(max-min);
}

