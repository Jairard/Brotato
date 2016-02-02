#include "catch.hpp"
#include <Core/Stainable.hpp>

SCENARIO("Stainable", "stainable")
{
	GIVEN("a stainable object")
	{
		Pot::Stainable<int> obj;

		THEN("it's clean at initialization")
		{
			CHECK_FALSE(obj.isRotten());
		}

		THEN("it's equal to itself")
		{
			obj.wash();
			CHECK(obj == obj);
			CHECK_FALSE(obj.isRotten());
		}

		THEN("it can be set")
		{
			obj.wash();
			obj = 42;
			CHECK(obj.isRotten());
			CHECK(obj.const_object() == 42);
			CHECK(obj.object() == 42);
			CHECK(obj == 42);

			obj.wash();
			obj.object() = 56;
			CHECK(obj.isRotten());
			CHECK(obj.const_object() == 56);
			CHECK(obj.object() == 56);
			CHECK(obj == 56);
		}

		THEN("it gets rotten correctly")
		{
			obj.wash();
			int v = obj.const_object();
			CHECK_FALSE(obj.isRotten());

			v = obj.object();
			CHECK(obj.isRotten());
		}

		THEN("it can be copied")
		{
			obj.wash();
			Pot::Stainable<int> copy(obj);
			CHECK_FALSE(obj.isRotten());
			CHECK(copy.isRotten());
			CHECK(copy == obj);

			Pot::Stainable<int> copy2 = obj;
			CHECK_FALSE(obj.isRotten());
			CHECK(copy2.isRotten());
			CHECK(copy2 == obj);
			CHECK(copy2 == copy);
		}

		THEN("it can be soiled and washed")
		{
			obj.wash();
			CHECK_FALSE(obj.isRotten());
			obj.soil();
			CHECK(obj.isRotten());
		}
	}
}
