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

    /* Boxes */
    RectangleShape rect2(&world, sf::Vector2f(0.5, 1.), sf::Vector2f(2., 2.), 0., sf::Color::Blue, b2_dynamicBody);
    RectangleShape rect(&world, sf::Vector2f(0., 20.), sf::Vector2f(2., 2.), 1., sf::Color::Red, b2_dynamicBody);

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
        world.DrawDebugData();
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
}
