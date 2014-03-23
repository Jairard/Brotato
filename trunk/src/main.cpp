#include <cstdio>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Render.hpp"
#include "RectangleShape.hpp"
#include "Math.hpp"
#include "Vector2.hpp"
#include "Physics/World.hpp"
#include "Graphics.hpp"

void handleEvents(sf::RenderWindow& window);

int main(int argc, char* argv[])
{	
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

    /* World */
    Vector2f gravity(0.0f, -10.0f);
	float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
	Phy::World world(gravity.toBox2D(), timeStep, velocityIterations, positionIterations);

    /* Ground */
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    /* Boxes */
    RectangleShape rect2(&world, sf::Vector2f(0.5, 1.), sf::Vector2f(2., 2.), Math::pi()/4., sf::Color::Blue, b2_dynamicBody);
    RectangleShape rect(&world, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 1., sf::Color::Red, b2_dynamicBody);
	
	rect2.build();
	rect.build();
	
	Graphics::SegmentShape segment(Vector2f(-20., -20.), Vector2f(20., 20.));
	segment.setColors(sf::Color::Yellow, sf::Color::Magenta);
	
	Graphics::PointShape p1(Vector2f(-10., 10.));
	Graphics::PointShape p2(Vector2f(10., -10.));
	p1.setColor(sf::Color::Green);
	p2.setColor(sf::Color::Cyan);
	
	Graphics::RectangleShape rectangle(Vector2f(2., 2.), Vector2f(10., -10.));
	rectangle.setColor(sf::Color::Yellow);

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

        world.step();
        //world.DrawDebugData();

        window.draw(rect);
        window.draw(rect2);
		window.draw(segment);
		window.draw(rectangle);
		window.draw(p1);
		window.draw(p2);

        window.display();

        float elapsed = clock.getElapsedTime().asSeconds();
        sf::Time toSleep = sf::seconds(timeStep - elapsed);

        if (toSleep.asSeconds() > 0)
            sf::sleep(toSleep);
        clock.restart();
    }
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
