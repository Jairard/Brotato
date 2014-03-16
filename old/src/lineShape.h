#ifndef LINESHAPE_H
#define LINESHAPE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "vector2.h"

class LineShape: public sf::RectangleShape
{
	public:
		LineShape(double thickness=1.);
		LineShape(float x0, float y0, float x1, float y1, double thickness=1.);
		LineShape(const Vector2f& p1, const Vector2f& p2, double thickness=1.);
		virtual ~LineShape() {}

		const Vector2f& firstPoint(void) const  { return _p1; }
		void setFirstPoint(const Vector2f& p);
		void setFirstPoint(float x, float y)    { setFirstPoint(Vector2f(x, y)); }

		const Vector2f& secondPoint(void) const { return _p2; }
		void setSecondPoint(const Vector2f& p);
		void setSecondPoint(float x, float y)   { setSecondPoint(Vector2f(x, y)); }

		double thickness(void) const            { return _thickness; }
		void setThickness(double thickness);

	protected:
		static const Vector2f _ref;
		Vector2f _p1, _p2, _center;
		double _thickness, _baseAngle;

	private:
		Vector2f *_r1, *_r2;
		void init(const Vector2f& p1, const Vector2f& p2, double thickness);
		void updatePositions(void);
		void updateThickness(void);
};

#endif
