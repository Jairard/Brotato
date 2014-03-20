#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

class Math
{
	public:
		static const double RAD_2_DEG;
		
		static float rad2deg(float angle);
		static float deg2rad(float angle);
		static double precisePi(void);
		static float pi(void);
};

#endif
