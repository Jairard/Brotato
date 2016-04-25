#include "catch.hpp"
#include <Core/Math.hpp>

SCENARIO("Math", "math")
{
	THEN("deg/rad conversions are correct")
	{
		CHECK(Pot::Math::deg2rad(   0.f) == Approx(  0.f * M_PI));
		CHECK(Pot::Math::deg2rad(  90.f) == Approx( 0.5f * M_PI));
		CHECK(Pot::Math::deg2rad( 180.f) == Approx(  1.f * M_PI));
		CHECK(Pot::Math::deg2rad( 360.f) == Approx(  2.f * M_PI));
		CHECK(Pot::Math::deg2rad(- 90.f) == Approx(-0.5f * M_PI));
		CHECK(Pot::Math::deg2rad(-180.f) == Approx(- 1.f * M_PI));
		CHECK(Pot::Math::deg2rad(-360.f) == Approx(- 2.f * M_PI));

		CHECK(Pot::Math::rad2deg(  0.f * M_PI) == Approx(   0.f));
		CHECK(Pot::Math::rad2deg( 0.5f * M_PI) == Approx(  90.f));
		CHECK(Pot::Math::rad2deg(  1.f * M_PI) == Approx( 180.f));
		CHECK(Pot::Math::rad2deg(  2.f * M_PI) == Approx( 360.f));
		CHECK(Pot::Math::rad2deg(-0.5f * M_PI) == Approx(- 90.f));
		CHECK(Pot::Math::rad2deg(- 1.f * M_PI) == Approx(-180.f));
		CHECK(Pot::Math::rad2deg(- 2.f * M_PI) == Approx(-360.f));
	}

	THEN("pi value is coherent")
	{
		CHECK(Pot::Math::pi() == Approx(Pot::Math::precisePi()));
	}

	GIVEN("an angle")
	{
		const float angle = 4.567f;

		THEN("it's not modified by chained rad/deg conversions")
		{
			REQUIRE(angle == Approx(Pot::Math::rad2deg(Pot::Math::deg2rad(angle))).epsilon(1E-7f));
			REQUIRE(angle == Approx(Pot::Math::deg2rad(Pot::Math::rad2deg(angle))).epsilon(1E-7f));
		}
	}

	THEN("clamp method is correct")
	{
		CHECK(Pot::Math::clamp( 0, 100, 42) == 42);
		CHECK(Pot::Math::clamp(42, 100, 42) == 42);
		CHECK(Pot::Math::clamp( 0,  42, 42) == 42);
		CHECK(Pot::Math::clamp(50, 100, 42) == 50);
		CHECK(Pot::Math::clamp( 0,  25, 42) == 25);

		CHECK(Pot::Math::clamp( 0.f, 100.f, 42.f) == 42.f);
		CHECK(Pot::Math::clamp(42.f, 100.f, 42.f) == 42.f);
		CHECK(Pot::Math::clamp( 0.f,  42.f, 42.f) == 42.f);
		CHECK(Pot::Math::clamp(50.f, 100.f, 42.f) == 50.f);
		CHECK(Pot::Math::clamp( 0.f,  25.f, 42.f) == 25.f);

		CHECK(Pot::Math::clamp( 0., 100., 42.) == 42.);
		CHECK(Pot::Math::clamp(42., 100., 42.) == 42.);
		CHECK(Pot::Math::clamp( 0.,  42., 42.) == 42.);
		CHECK(Pot::Math::clamp(50., 100., 42.) == 50.);
		CHECK(Pot::Math::clamp( 0.,  25., 42.) == 25.);
	}

	THEN("lerp method is correct")
	{
		float f1 = 5.5f, f2 = 8.5f;
		CHECK(Pot::Math::lerp(f1, f2, 0.f) == f1);
		CHECK(Pot::Math::lerp(f1, f2, 1.f) == f2);
		CHECK(Pot::Math::lerp(f2, f1, 0.f) == f2);
		CHECK(Pot::Math::lerp(f2, f1, 1.f) == f1);
		CHECK(Pot::Math::lerp(f1, f2, 0.5f) == Pot::Math::lerp(f2, f1, 0.5f));
		CHECK(Pot::Math::lerp(f1, f2, 0.5f) == 7.f);

		Pot::Vector2f v1(2.5f, 6.8f), v2(3.f, 8.8f);
		CHECK(Pot::Math::lerp(v1, v2, 0.f) == v1);
		CHECK(Pot::Math::lerp(v1, v2, 1.f) == v2);
		CHECK(Pot::Math::lerp(v2, v1, 0.f) == v2);
		CHECK(Pot::Math::lerp(v2, v1, 1.f) == v1);
		CHECK(Pot::Math::lerp(v1, v2, 0.5f) == Pot::Math::lerp(v2, v1, 0.5f));
		CHECK(Pot::Math::lerp(v1, v2, 0.5f) == Pot::Vector2f(2.75f, 7.8f));
	}
}
