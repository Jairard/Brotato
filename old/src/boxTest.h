#ifndef BOXTEST_H
#define BOXTEST_H

#include <math.h>

#define BOX_COUNT				200
#define BOX_SIZE				.1f
#define MAX_ANGULAR_VELOCITY	(2*M_PI)
#define MARGIN					(BOX_SIZE/2.)

void boxTest(void);
double between(double min, double max);

#endif
