#include <stdio.h>
#include <math.h>
#include "math/trigo.h"

// Function to calculate the values of trigonometric functions
double trigo(double x, int r) {
	double rad = x * (M_PI / 180.0); // Converting degrees to radians
	double result;
	switch(r) {
		case 1:
			result = sin(rad);
			return (fabs(result) < EPSILON) ? 0.0 : result;
		case 2:
			result = cos(rad);
			return (fabs(result) < EPSILON) ? 0.0 : result;
		case 3:
			result = tan(rad);
			return (fabs(result) < EPSILON) ? INFINITY : result;
		case 4:
			result = tan(rad);
			return (fabs(result) < EPSILON) ? INFINITY : 1 / result;
		case 5:
			result = cos(rad);
			return (fabs(result) < EPSILON) ? INFINITY : 1 / result;
		case 6:
			result = sin(rad);
			return (fabs(result) < EPSILON) ? INFINITY : 1 / result;
		default:
			printf("Invalid trigonometric function choice.\n");
			return NAN;  // Default return value when no case matches
	}
}