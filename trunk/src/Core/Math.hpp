#ifndef __CORE_MATH__
#define __CORE_MATH__

#include <cmath>
#include "NonInstantiable.hpp"

class Math: public NonInstantiable
{
	public:
		static const double RAD_2_DEG;
		
		static float rad2deg(float angle);
		static float deg2rad(float angle);
		static double precisePi(void);
		static float pi(void);
};

#endif
