#include "catch.hpp"
#include <DnaSystem/BaseOrganism.hpp>
#include <DnaSystem/DNA.hpp>
#include <DnaSystem/Collector.hpp>

using Pot::DnaSystem::Collector;

SCENARIO("DNA-Organism system", "dna-organism system")
{
	class BaseOrganism: public Pot::DnaSystem::BaseOrganism
	{};
	typedef Pot::DnaSystem::DNA<BaseOrganism> BaseOrganismDNA;

	class DerivedOrganism: public BaseOrganism
	{};
	typedef Pot::DnaSystem::DNA<DerivedOrganism> DerivedOrganismDNA;

	GIVEN("a derived organism")
	{
		Collector::instantiate();
		const Collector& collector = Collector::instance();

		const DerivedOrganism* const organism = new DerivedOrganism();
		{
			const DerivedOrganismDNA dna(organism);
			THEN("we can instantiate a DNA from it")
			{
				CHECK(dna.isValid());
				CHECK(collector.organismCount() == 1);
				CHECK(collector.dnaCount() == 1);
			}

			const BaseOrganismDNA upcasted(dna);
			THEN("we can instantiate an upper-class DNA from it")
			{
				CHECK(upcasted.isValid());
				CHECK(collector.organismCount() == 1);
				CHECK(collector.dnaCount() == 2);
			}

			const DerivedOrganismDNA downcasted(upcasted);
			THEN("we can downcast an upper-class DNA of this instance")
			{
				CHECK(downcasted.isValid());
				CHECK(collector.organismCount() == 1);
				CHECK(collector.dnaCount() == 3);
			}

			THEN("we can create a scoped copy")
			{
				const DerivedOrganismDNA copyDna(dna);
				CHECK(copyDna.isValid());
				CHECK(collector.organismCount() == 1);
				CHECK(collector.dnaCount() == 4);
			}

			THEN("it's correctly cleaned")
			{
				CHECK(collector.organismCount() == 1);
				CHECK(collector.dnaCount() == 3);
			}
		}

		THEN("the collector is empty when all the DNAs are destroyed")
		{
			CHECK(collector.organismCount() == 0);
			CHECK(collector.dnaCount() == 0);
		}

		delete organism;
		Collector::deleteInstance();
	}

	GIVEN("a class that inherits from Pot::BaseOrganism")
	{
		THEN("we can't default-construct a DNA of this type")
		{
			//BaseOrganismDNA privatizeDefaultConstructor; // Invalid constructor -> compilation error
			// TODO: check compilation error ?
		}

		THEN("we can't construct a DNA of its type from nullptr")
		{
			//BaseOrganismDNA assertOnNullPointerOrganism(nullptr);  // Can't construct from nullptr -> assert
			// TODO: test assert occured ?
		}
	}

	GIVEN("a base organism instance")
	{
		Collector::instantiate();
		const BaseOrganism* const organism = new BaseOrganism();

		{
			THEN("we can instantiate a DNA of its type")
			{
				const BaseOrganismDNA dna(organism);
				CHECK(dna.isValid());
			}

			THEN("we can't instantiate a DNA of derived type")
			{
				//DerivedOrganismDNA derivedDna(organism); // Bad cast -> assert
				// TODO: test assert occured ?
			}
		}

		delete organism;
		Collector::deleteInstance();
	}

	GIVEN("a derived organism instance")
	{
		Collector::instantiate();
		const DerivedOrganism* const organism = new DerivedOrganism();

		{
			THEN("we can instantiate a DNA of its type")
			{
				const DerivedOrganismDNA dna(organism);
				CHECK(dna.isValid());
			}
		}

		delete organism;
		Collector::deleteInstance();
	}

	GIVEN("a derived organism instance that has been upcasted")
	{
		Collector::instantiate();
		const BaseOrganism* const organism = new DerivedOrganism();

		{
			THEN("we can instantiate a DNA of its original type")
			{
				const DerivedOrganismDNA dna(organism);
				CHECK(dna.isValid());
			}

			THEN("we can instantiate a DNA of its parent type")
			{
				const BaseOrganismDNA dna(organism);
				CHECK(dna.isValid());
			}
		}

		delete organism;
		Collector::deleteInstance();
	}
}
