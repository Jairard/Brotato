#include "../stdafx.h"
#include "catch.hpp"
#include "../Core/AARect.hpp"
#include "../Core/Rect.hpp"

SCENARIO("AARect", "rect")
{
	GIVEN("an AARect")
	{
		Pot::AARect r1(3.f, 4.f, 5.f, 6.f);
		
		THEN("it's equal to itself")
		{
			CHECK(r1 == r1);
		}
		
		THEN("at's correctly copied")
		{
			Pot::AARect r2 = r1;
			CHECK(r1 == r2);
			CHECK(r2 == r1);
			
			Pot::AARect r3(r1);
			CHECK(r3 == r1);
			CHECK(r1 == r3);
			
			CHECK(Pot::AARect(r1) == r1);
			CHECK(r1 == Pot::AARect(r1));
		}
	}
	
	GIVEN("two identicaly initialized AARects")
	{
		Pot::AARect r1(3.f, 4.f, 5.f, 6.f);
		Pot::AARect r2(3.f, 4.f, 5.f, 6.f);
		
		THEN("they are equal")
		{
			CHECK(r1 == r2);
			CHECK(r2 == r1);
		}
	}
	
	GIVEN("an AARect initialized with center")
	{
		Pot::AARect rect(Pot::Vector2f(5.f, 10.f), Pot::Vector2f(4.f, 6.f));
		
		THEN("the center is correctly set")
		{
			CHECK(rect.left == 3.f);
			CHECK(rect.bottom == 7.f);
			CHECK(rect.width == 4.f);
			CHECK(rect.height == 6.f);
		}
	}
}

SCENARIO("Rect", "rect")
{
	GIVEN("a Rect")
	{
		Pot::Rect r1(Pot::Vector2f(0.f, 0.f),
		             Pot::Vector2f(5.F, 3.4f),
		             Pot::Vector2f(32.4f, 65.3f),
		             Pot::Vector2f(1.08f, 5.263f));
		
		THEN("it's equal to itself")
		{
			CHECK(r1 == r1);
		}
		
		THEN("it's correctly copied")
		{
			Pot::Rect r2 = r1;
			CHECK(r1 == r2);
			CHECK(r2 == r1);
			
			Pot::Rect r3(r1);
			CHECK(r3 == r1);
			CHECK(r1 == r3);
			
			CHECK(Pot::Rect(r1) == r1);
			CHECK(r1 == Pot::Rect(r1));
		}
	}
		
	GIVEN("two identicaly initialized AARects")
	{
		Pot::Rect r1(Pot::Vector2f(0.f, 0.f),
		             Pot::Vector2f(5.F, 3.4f),
		             Pot::Vector2f(32.4f, 65.3f),
		             Pot::Vector2f(1.08f, 5.263f));
		Pot::Rect r2(Pot::Vector2f(0.f, 0.f),
		             Pot::Vector2f(5.F, 3.4f),
		             Pot::Vector2f(32.4f, 65.3f),
		             Pot::Vector2f(1.08f, 5.263f));

		THEN("they are equal")
		{
			CHECK(r1 == r2);
			CHECK(r2 == r1);
		}
	}
}
