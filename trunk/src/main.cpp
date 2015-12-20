#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//#define DEBUG

#include "PotatoEngine/stdafx.h"
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "PotatoEngine/Core/Pool.hpp"
#include "PotatoEngine/Core/ClassHelpers.hpp"
#include "PotatoEngine/Core/LibsHelpers.hpp"
#include "PotatoEngine/Core/Transform.hpp"
#include "PotatoEngine/Debug/Logger.hpp"
#include "PotatoEngine/PotatoPlant.hpp"
#include "PotatoEngine/Potato.hpp"
#include "PotatoEngine/RenderCell.hpp"

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
	POT_UNUSED(argc);
	POT_UNUSED(argv);
	
	Pot::PotatoPlant plant("Potatoes gonna potate", sf::VideoMode(400, 400));
	return plant.loop();
}
