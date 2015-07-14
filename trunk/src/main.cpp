#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define DEBUG

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Window.hpp"
#include "Core.hpp"
#include "Graphics.hpp"
#include "Physics.hpp"
#include "GameObjects.hpp"
#include "Debug/CallStack.hpp"
#include "PotatoEngine/PotatoPlant.hpp"
#include "PotatoEngine/Potato.hpp"
#include "Core/Pool.hpp"
#include "PotatoEngine/Core/ClassHelpers.hpp"
#include "PotatoEngine/Core/LibsHelpers.hpp"

/*
Does not work :( (see Potato)
class PoolChunk
{
	template <typename T> friend class Pool;
	
	private:
		PoolChunk();
		int m_data[512];
};

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	Pool<PoolChunk> pool;
	return EXIT_SUCCESS;
}
//*/

void scene2(void);
void scene3(void);

//*
#include "PotatoEngine/RenderCell.hpp"
#include "PotatoEngine/Debug/Logger.hpp"

/*
template<typename... Args>
void initialize(Args... args)
{
	std::cout << "nope :(" << std::endl;
	VUNUSED(args);
}

template<>
void initialize<Pot::RenderCell*, sf::RenderTarget*>(Pot::RenderCell* cell, sf::RenderTarget* target)
{
	std::cout << "yay !" << std::endl;
	//m_target = target;
}
*/

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	Pot::PotatoPlant plant("First plant !", sf::VideoMode(400, 400));
	return plant.loop();
}
//*/

void scene2()
{
	Logger::enableTag("test");
	
	/* Window */
	Window window(sf::VideoMode(400, 400), "Window test");
	sf::View view(sf::Vector2f(), sf::Vector2f(50., -50.));
	
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

void scene3()
{
	Logger::enableTag("gameObject");
	
	sf::View view(sf::Vector2f(), sf::Vector2f(50., -50.));
	Window window(sf::VideoMode(400, 400), "Window test");
	
	GameObject go("test");
	Graphics::GeometryComponent* geometry = new Graphics::GeometryComponent(sf::Quads, 4);
	Graphics::RenderComponent* renderer = new Graphics::RenderComponent(window);
	
	go.addComponent(geometry);
	go.addComponent(renderer);
	
	window.setView(view);
	
	/*
	Vector2f gravity(0.0f, -10.0f);
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Phy::World world(gravity, timeStep, velocityIterations, positionIterations);
	Game* game = new Game(window, &world);
	
	window.setView(view);
	window.setGame(game);
	window.loop();
	*/
	
	Scene scene("proute");
	scene.addGameObject(&go);
	
	GameObject subroot1("subroot1"), subroot2("subroot2"), child1("child");
	scene.addGameObject(&subroot1);
	scene.addGameObject(&subroot2);
	scene.setParent(&child1, &subroot1);
	scene.setParent(&subroot1, &subroot2);
	scene.log("Warning");
	scene.setParent(&child1, child1.parent()->parent());
	scene.log("gameObject");
	//Bug
	//scene.setParent(&scene.root(), &go);
}
