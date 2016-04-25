#include "../stdafx.h"
#include "catch.hpp"
#include "../Core/LibsHelpers.hpp"

SCENARIO("LibsHelpers", "helpers")
{
	GIVEN("a Pot::Vectof2f")
	{
		Pot::Vector2f v(4.2f, 13.37f);

		THEN("it can be converted to sf::Vector2f and b2Vec2")
		{
			sf::Vector2f sfv = pv_2_sfv(v);
			CHECK(v.x == sfv.x);
			CHECK(v.y == sfv.y);
			
			b2Vec2 b2v = pv_2_b2v(v);
			CHECK(v.x == b2v.x);
			CHECK(v.y == b2v.y);
		}

		THEN("it's not modified by chained conversions")
		{
			CHECK(v == sfv_2_pv(pv_2_sfv(v)));
			CHECK(v == b2v_2_pv(pv_2_b2v(v)));
			CHECK(v == sfv_2_pv(b2v_2_sfv(pv_2_b2v(v))));
			CHECK(v == b2v_2_pv(sfv_2_b2v(pv_2_sfv(v))));
		}
	}

	GIVEN("an sf::Vectof2f")
	{
		sf::Vector2f v(4.2f, 13.37f);
		
		THEN("it can be converted to Pot::Vector2f and b2Vec2")
		{
			Pot::Vector2f pv = sfv_2_pv(v);
			CHECK(v.x == pv.x);
			CHECK(v.y == pv.y);
			
			b2Vec2 b2v = sfv_2_b2v(v);
			CHECK(v.x == b2v.x);
			CHECK(v.y == b2v.y);
		}
		
		THEN("it's not modified by chained conversions")
		{
			CHECK(v == pv_2_sfv(sfv_2_pv(v)));
			CHECK(v == b2v_2_sfv(sfv_2_b2v(v)));
			CHECK(v == pv_2_sfv(b2v_2_pv(sfv_2_b2v(v))));
			CHECK(v == b2v_2_sfv(pv_2_b2v(sfv_2_pv(v))));
		}
	}

	GIVEN("a b2Vec2")
	{
		b2Vec2 v(4.2f, 13.37f);

		THEN("it can be converted to Pot::Vector2f and sf::Vector2f")
		{
			Pot::Vector2f pv = b2v_2_pv(v);
			CHECK(v.x == pv.x);
			CHECK(v.y == pv.y);
			
			sf::Vector2f sfv = b2v_2_sfv(v);
			CHECK(v.x == sfv.x);
			CHECK(v.y == sfv.y);
		}

		THEN("it's not modified by chained conversions")
		{
			CHECK(v == pv_2_b2v(b2v_2_pv(v)));
			CHECK(v == sfv_2_b2v(b2v_2_sfv(v)));
			CHECK(v == pv_2_b2v(sfv_2_pv(b2v_2_sfv(v))));
			CHECK(v == sfv_2_b2v(pv_2_sfv(b2v_2_pv(v))));
		}
	}

	GIVEN("an sf::Color")
	{
		sf::Color c(128, 42, 35);

		THEN("it can be converted to b2Color")
		{
			b2Color b2c = sfc_2_b2c(c);
			const float coef = 1.f / 255.f;
			CHECK(b2c.r == (float)c.r * coef);
			CHECK(b2c.g == (float)c.g * coef);
			CHECK(b2c.b == (float)c.b * coef);
		}

		THEN("it's not modified by chained conversions")
		{
			CHECK(c == b2c_2_sfc(sfc_2_b2c(c)));
		}
	}

	GIVEN("a b2Color")
	{
		b2Color c(0.5f, 0.345f, 0.654f);

		THEN("it can be converted to b2Color")
		{
			sf::Color sfc = b2c_2_sfc(c);
			const float coef = 255.f;
			const float maxError = 0.f;//1.f;
			
			CHECK(fabsf(sfc.r - c.r * coef) < 1.f);
			CHECK(fabsf(sfc.g - c.g * coef) < 1.f);
			CHECK(fabsf(sfc.b - c.b * coef) < 1.f);
		}

		THEN("it's not modified by chained conversions")
		{
			b2Color converted = sfc_2_b2c(b2c_2_sfc(c));
			const float maxError = 1.f / 255.f;

			CHECK(fabsf(converted.r - c.r) < maxError);
			CHECK(fabsf(converted.g - c.g) < maxError);
			CHECK(fabsf(converted.b - c.b) < maxError);
		}
	}

	GIVEN("a Pot::AARect")
	{
		Pot::AARect paar(1.1f, 2.3f, 4.6f, 56.7f);

		THEN("it can be converted to sf::FloatRect")
		{
			sf::FloatRect sfr = paar_2_sfr(paar);
			CHECK(paar.left == sfr.left);
			CHECK(paar.bottom == sfr.top);
			CHECK(paar.width == sfr.width);
			CHECK(paar.height == sfr.height);
		}

		THEN("it can be converted to Pot::Rect")
		{
			CHECK(paar_2_pr(paar).AABB() == paar);
		}

		THEN("it's not modified by chained conversions")
		{
			Pot::AARect converted = sfr_2_paar(paar_2_sfr(paar));
			CHECK(paar.left == converted.left);
			CHECK(paar.bottom == converted.bottom);
			CHECK(paar.width == converted.width);
			CHECK(paar.height == converted.height);
		}
	}

	GIVEN("an sf::FloatRect")
	{
		sf::FloatRect sfr(1.1f, 2.3f, 4.6f, 56.7f);

		THEN("it can be converted to Pot::AARect")
		{
			Pot::AARect paar = sfr_2_paar(sfr);
			CHECK(sfr.left == paar.left);
			CHECK(sfr.top == paar.bottom);
			CHECK(sfr.width == paar.width);
			CHECK(sfr.height == paar.height);
		}

		THEN("it can be converted to Pot::Rect")
		{
			Pot::AARect rectAABB = sfr_2_pr(sfr).AABB();
			CHECK(sfr.left == rectAABB.left);
			CHECK(sfr.top == rectAABB.bottom);
			CHECK(sfr.width == rectAABB.width);
			CHECK(sfr.height == rectAABB.height);
		}

		THEN("it's not modified by chained conversions")
		{
			sf::FloatRect converted = paar_2_sfr(sfr_2_paar(sfr));
			CHECK(sfr.left == converted.left);
			CHECK(sfr.top == converted.top);
			CHECK(sfr.width == converted.width);
			CHECK(sfr.height == converted.height);
		}
	}
}
