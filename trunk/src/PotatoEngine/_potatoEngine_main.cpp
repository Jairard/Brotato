#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "PotatoPlant.hpp"

//#define DEBUG

/*
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Core/Pool.hpp"
#include "Core/ClassHelpers.hpp"
#include "Core/LibsHelpers.hpp"
#include "Core/Transform.hpp"
#include "Core/types.hpp"
#include "Debug/Logger.hpp"
#include "PotatoPlant.hpp"
#include "RenderCell.hpp"
//*/

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
	POT_UNUSED(argc);
	POT_UNUSED(argv);
	
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

#include "Core/Pool.hpp"
#include "DNA.hpp"
#include "BaseOrganism.hpp"
#include "DNACollector.hpp"

class FakeCell: public Pot::BaseOrganism
{
	public:
		FakeCell(): Pot::BaseOrganism() {}
		
		virtual ~FakeCell()
		{}
};

class FakeDerivedCell: public FakeCell
{
	public:
		FakeDerivedCell() {}
		virtual ~FakeDerivedCell() {}
};

//*
typedef Pot::DNA<FakeCell> FakeCellDNA;
typedef Pot::DNA<FakeDerivedCell> FakeDerivedCellDNA;

using Pot::Debug::Logger;
using Pot::DNACollector;

// Misc + upcast
void test1()
{
	DNACollector::instantiate();
	
	FakeDerivedCell* cell = new FakeDerivedCell();
	{
		FakeDerivedCellDNA dna(cell);
		ASSERT_DEBUG(dna.isValid());

		FakeCellDNA upcasted(dna);
		ASSERT_DEBUG(upcasted.isValid());
		
		DNACollector::dump(Logger::CWarning);
		
		FakeDerivedCellDNA downcasted(upcasted);
		ASSERT_DEBUG(downcasted.isValid());
		
		DNACollector::dump(Logger::CWarning);
		
		{
			FakeDerivedCellDNA copyDna(dna);
			ASSERT_DEBUG(copyDna.isValid());
			DNACollector::instance().dump(Logger::CWarning);
			Logger::log(Logger::CWarning, "cell(%u), dna(%u), copyDna(%u), parentDna(%u)", cell, &dna, &copyDna, &upcasted);
		}
		
		DNACollector::dump(Logger::CWarning);
		Logger::log(Logger::CWarning, "cell(%u), dna(%u), formChildDNA(%u)", cell, &dna, &upcasted);
	}
	
	DNACollector::dump(Logger::CWarning);
	delete cell;
	DNACollector::dump(Logger::CWarning);
	
	Pot::DNACollector::deleteInstance();
}

// Downcast
void test2()
{
	Pot::Logger::log(Pot::Logger::CWarning, "test 1");
	{
		DNACollector::instantiate();
		FakeCell* cell = new FakeCell();
		{
			FakeCellDNA baseDna(cell);
			ASSERT_DEBUG(baseDna.isValid());
		}
		delete cell;
		Pot::DNACollector::deleteInstance();
	}

	Pot::Logger::log(Pot::Logger::CWarning, "test 2");
	{
		DNACollector::instantiate();
		FakeDerivedCell* cell = new FakeDerivedCell();
		{
			FakeDerivedCellDNA derivedDna(cell); // Valid
			ASSERT_DEBUG(derivedDna.isValid());
		}
		delete cell;
		Pot::DNACollector::deleteInstance();
	}

	Pot::Logger::log(Pot::Logger::CWarning, "test 3");
	{
		DNACollector::instantiate();
		FakeCell* cell = new FakeDerivedCell();
		{
			FakeDerivedCellDNA derivedDna(cell); // Valid
			ASSERT_DEBUG(derivedDna.isValid());
		}
		delete cell;
		Pot::DNACollector::deleteInstance();
	}

	Pot::Logger::log(Pot::Logger::CWarning, "test 4");
	{
		DNACollector::instantiate();
		FakeCell* cell = new FakeCell();
		{
			//FakeDerivedCellDNA derivedDna(cell); // Bad cast -> assert
		}
		delete cell;
		Pot::DNACollector::deleteInstance();
	}

	Pot::Logger::log(Pot::Logger::CWarning, "test 5");
	{
		DNACollector::instantiate();
		const FakeCell* baseCell = new FakeDerivedCell();
		{
			FakeCellDNA baseDNA(baseCell);
			ASSERT_DEBUG(baseDNA.isValid());
			DNACollector::dump(Logger::CWarning);

			//FakeCellDNA privatizeDefaultConstructor;           // Invalid constructor -> compilation error
			//FakeCellDNA assertOnNullPointerOrganism(nullptr);  // Can't construct from nullptr -> assert
		}
		
		delete baseCell;
		Pot::DNACollector::deleteInstance();
	}
}

// Early organism deletion
void test3()
{
	DNACollector::instantiate();

	FakeCell* baseCell = new FakeCell();
	{
		FakeCellDNA dna(baseCell);
		delete baseCell;
		
		{
			DNACollector::dump(Logger::CWarning);
			FakeCellDNA invalidCopy(dna);
			DNACollector::dump(Logger::CWarning);
		}
	}

	DNACollector::deleteInstance();
}

// Pool
void test4()
{
	// Pool test not valid because pool doesn't support inheritance ...
	// TODO: manual organism handling in pool (via template bool)
	/*
	DNACollector::instantiate();

	{
		Pot::Pool<FakeCell> pool(1);
		FakeCell* cell = pool.create();
		FakeCellDNA dna(cell);
		DNACollector::dump(Logger::CWarning);
		
		pool.destroy(cell);
		FakeCell* cell2 = pool.create();
		ASSERT_DEBUG(cell == cell2);
		
		FakeCellDNA dna2(cell2);
		DNACollector::dump(Logger::CWarning);
	}
	
	DNACollector::deleteInstance();
	//*/
}

#include "Debug/Callstack.hpp"
#include "Debug/SignalHandler.hpp"

int main(int argc, char* argv[])
{
	ASSERT_RELEASE(argc > 0);
	Pot::Debug::AbstractCallstack::setProgramName(argv[0]);
	Pot::Debug::SignalHandler::setup();

	Logger::enableTag(Logger::CAssert);
	Logger::enableTag(Pot::DNACollector::tag());
	Logger::log(Logger::CWarning, "");

    Logger::log(Logger::CWarning, "Callstack:\n%s", Pot::Debug::Callstack()());

    /*
	test1();
	test2();
	test3();
	test4();
    //*/

	return EXIT_SUCCESS;
	
	Pot::PotatoPlant plant("Potatoes gonna potate", sf::VideoMode(400, 400));
	return plant.loop();
}
