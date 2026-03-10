#include <stdio.h>
#include <math.h>
#include "core/math_constants.h"
#include "math/trigo.h"

/* KNOWN BEHAVIOUR: tan(90deg), cot(0deg), sec(90deg), cosec(0deg)
 * Currently returns MATHINATOR_UNDEF with stderr output.
 * FUTURE: Consider treating INFINITY as valid stdout result
 * for engineering/piping use cases where caller handles inf.
 * Tracked for edge-case handling pass after all modules complete.
 */

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