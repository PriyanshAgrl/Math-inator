#ifndef TRIGO_H
#define TRIGO_H

// Defining Precision Tolerance
#define ZERO_TOLERANCE 1e-10
// Defining Value of Pi
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define DEG_TO_RAD (M_PI / 180.0)

// Trigonometric functions
double trigo_sin(double radian);
double trigo_cos(double radian);
double trigo_tan(double radian);
double trigo_cot(double radian);
double trigo_sec(double radian);
double trigo_cosec(double radian);

#endif