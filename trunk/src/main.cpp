#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
}
//*/

#include <PotatoPlant.hpp>
#include <Core/BuildConfig.hpp>
#include <Core/Pool.hpp>
#include <Debug/Callstack.hpp>
#include <Debug/Logger.hpp>
#include <Debug/SignalHandler.hpp>

using Pot::Debug::Logger;

int main(int argc, char* argv[])
{
	ASSERT_RELEASE(argc > 0);
	Pot::Debug::AbstractCallstack::setProgramName(argv[0]);
	Pot::Debug::SignalHandler::setup();

	Logger::enableTag(Logger::CInfo);
	Logger::enableTag(Logger::CAssert);
	Logger::log(Logger::CInfo, "");

	return EXIT_SUCCESS;

	const std::string windowTitle = "Potatoes gonna potate - " + Pot::BuildConfig::osAsString + " - " + Pot::BuildConfig::buildAsString;
	Pot::PotatoPlant plant(windowTitle.c_str(), sf::VideoMode(400, 400));
	return plant.loop();
}
