#ifndef ARITHMETIC_H
#define ARITHMETIC_H

double add(float x, float y);      // Adds two numbers and returns the result
double subtract(float x, float y); // Subtracts y from x and returns the result
double product(float x, float y);  // Multiplies two numbers and returns the result
double divide(float x, float y);   // Divides x by y and returns the result
int rem(int x, int y);             // Calculates the remainder of x divided by y
double sqroot(float x);            // Computes the square root of x
double power(float x, float y);    // Raises x to the power of y
int fact(int x);                   // Calculates the factorial of x
double logarithm(float x, float b);   // Log of (x) to the base b

#endif