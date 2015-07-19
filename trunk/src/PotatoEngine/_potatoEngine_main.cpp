#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define DEBUG

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Core/Pool.hpp"
#include "Core/ClassHelpers.hpp"
#include "Core/LibsHelpers.hpp"
#include "Core/Transform.hpp"
#include "Debug/Logger.hpp"
#include "PotatoPlant.hpp"
#include "Potato.hpp"
#include "RenderCell.hpp"

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
//*/

int main(int argc, char* argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	Pot::PotatoPlant plant("Potatoes gonna potate", sf::VideoMode(400, 400));
	return plant.loop();
}
