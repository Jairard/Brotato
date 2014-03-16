#ifndef PHYWORLD_H
#define PHYWORLD_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <iostream>

#include "vector2.h"
#include "phyObject.h"

//class PhyObject;

class PhyWorld: public b2World, public sf::Transformable
{
	public:
		PhyWorld(const Vector2f& gravity=DEFAULT_GRAVITY,
				 double timeStep=DEFAULT_TIME_STEP,
				 uint32 velocityIt=DEFAULT_VELOCITY_ITERATIONS,
				 uint32 positionIt=DEFAULT_POSITION_ITERATIONS);

		void Step();
		void addObject(PhyObject* obj)      { _objects.push_back(obj); }

		double timeStep(void) const         { return _timeStep; }
		void setTimeStep(double timeStep)	{ _timeStep = (timeStep > 0. ? timeStep : DEFAULT_TIME_STEP); }

		//*
		/* The origin of the world is always (0, 0) */
		//void setOrigin(Vector2f origin)     { return; }
		void setScale(double scale);
		void setScale(double scaleX, double scaleY);
		void setScale(const Vector2f& scale);
		const Vector2f getScale(void) const    { return Vector2f(sf::Transformable::getScale()); }
		Vector2f screenPoint(const Vector2f& phyPoint) const;
		Vector2f phyPoint(const Vector2f& screenPoint) const;
		double screenAngle(double phyAngle) const;
		double phyAngle(double screenAngle) const;
		Vector2f screenVector(const Vector2f& phyVector) const;
		Vector2f phyVector(const Vector2f& screenVector) const;
		/*/
		float32 scale(void) const           { return _scale; }
		void setScale(float32 scale)        { _scale = scale; }

		sf::Vector2f translation(void) const                    { return sf::Vector2f(_translation.x, _translation.y); }
		void setTranslation(const sf::Vector2f& translation)    { setTranslation(b2Vec2(translation.x, translation.y)); }
		void setTranslation(const b2Vec2& translation)			{ _translation = translation; }
		//*/

		static const Vector2f DEFAULT_GRAVITY;
		static const double DEFAULT_TIME_STEP;
		static const unsigned int DEFAULT_VELOCITY_ITERATIONS;
		static const unsigned int DEFAULT_POSITION_ITERATIONS;

	protected:
		double _timeStep;
		uint32 _velocityIterations, _positionIterations;
		std::vector<PhyObject*> _objects;
};

#endif
