#include "../stdafx.h"
#include "catch.hpp"
#include "../Core/Pool.hpp"

SCENARIO("Pool", "pool")
{
	GIVEN("Aa int pool")
	{
		Pot::Pool<int> pool;

		THEN("initialization was OK")
		{
			CHECK(pool.capacity() > 0);
			CHECK(pool.availableChunkCount() > 0);
			CHECK(pool.usedChunkCount() == 0);
			CHECK_FALSE(pool.isFull());
		}

		THEN("we can create an object")
		{
			size_t oldUsedChunkCount = pool.usedChunkCount();
			size_t oldAvailableChunkCount = pool.availableChunkCount();

			int* v = pool.create();
			CHECK(pool.usedChunkCount() == oldUsedChunkCount + 1);
			CHECK(pool.availableChunkCount() == oldAvailableChunkCount - 1);

			THEN("we can destroy it")
			{
				pool.destroy(v);
				CHECK(pool.usedChunkCount() == oldUsedChunkCount);
				CHECK(pool.availableChunkCount() == oldAvailableChunkCount);
			}
		}

		THEN("we can create several objects")
		{
			size_t oldUsedChunkCount = pool.usedChunkCount();
			size_t oldAvailableChunkCount = pool.availableChunkCount();

			int *v1 = pool.create(), *v2 = pool.create();
			CHECK(pool.usedChunkCount() == oldUsedChunkCount + 2);
			CHECK(pool.availableChunkCount() == oldAvailableChunkCount - 2);

			THEN("we can destroy them")
			{
				pool.destroy(v1);
				pool.destroy(v2);
				CHECK(pool.usedChunkCount() == oldUsedChunkCount);
				CHECK(pool.availableChunkCount() == oldAvailableChunkCount);
			}
		}
	}
}

