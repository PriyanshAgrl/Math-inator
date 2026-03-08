#include <stdio.h>
#include <math.h>
#include "math/trigo.h"

double trigo_sin(double radian){
	double result = sin(radian);
	return (fabs(result) < ZERO_TOLERANCE) ? 0.0 : result;
}
double trigo_cos(double radian){
	double result = cos(radian);
	return (fabs(result) < ZERO_TOLERANCE) ? 0.0 : result;
}
double trigo_tan(double radian){
	if (fabs(cos(radian)) < ZERO_TOLERANCE)
        return INFINITY;
    return tan(radian);
}
double trigo_cot(double radian){
	if (fabs(sin(radian)) < ZERO_TOLERANCE)
        return INFINITY;
    return cos(radian)/sin(radian);
}
double trigo_sec(double radian){
	if (fabs(cos(radian)) < ZERO_TOLERANCE)
        return INFINITY;
    return 1.0 / cos(radian);
}
double trigo_cosec(double radian){
	if (fabs(sin(radian)) < ZERO_TOLERANCE)
        return INFINITY;
    return 1.0 /sin(radian);
}