#include <stdio.h>
#include <math.h>
#include "arithmetic.h"
// Function to add two numbers and return the result
double add(float x, float y) {
  return x + y;
}

// Function to subtract the second number from the first and return the result
double subtract(float x, float y) {
  return x - y;
}

// Function to multiply two numbers and return the result
double product(float x, float y) {
  return x * y;
}

// Function to divide the first number by the second and return the result
double divide(float x, float y) {
  // Check if the divisor is 0 to prevent division by zero
  if (y == 0) {
    printf("Error: Division by zero is undefined.\nPlease enter a Non-Zero Number\n");
    return NAN; // Returning 'Not a Number' to indicate an error condition
  }
  return x / y;
}

// Function to calculate the remainder when the first number is divided by the second
int rem(int x, int y) {
  return x % y;
}

// Function to compute the square root of a number
double sqroot(float x) {
  // Checking if the input is negative to prevent imaginary results
  if (x < 0) {
    printf("Error: Square Root of negative number is not Real.\n");
    return NAN; // Returning 'Not a Number' to indicate an error condition
  }
  return sqrt(x);
}

// Function to raise the first number to the power of the second
double power(float x, float y) {
  // Checking if the exponent is negative
  if (y < 0) {
    // Handling negative exponents by calculating the reciprocal of positive exponent
    double result = pow(x, -y);
    return (result == 0) ? INFINITY : 1.0 / result;
  }
  // If exponent is non-negative, use the standard pow function
  return pow(x, y);
}

// Function to calculate the factorial of a non-negative integer
int fact(int x) {
  // Checking if the input is a non-negative integer
  if (x < 0 || (int)x != x) {
    printf("Error: Factorial input must be a non-negative integer.\nPlease input a positive whole number.\n");
    return NAN; // Returning 'Not a Number' to indicate an error condition
  }
  // Base cases: 0! is 1 and 1! is 1
  if (x == 0 || x == 1) {
    return 1;
  }
/*
  int factN = fact(x-1) * x; // Recursive case: x! = x * (x-1)!
  Cancelled recursion because of potential stack overflow
*/
  // Iterative approach: x! = x * (x-1) * (x-2) * ... * 1
  // Calculate the factorial iteratively
  int factN = 1;
  for (int i = 1; i <= x; i++) { // Iterative approach: x! = 1 * 2 * ... * (x-1) * x
    factN *= i;
  } 
  return factN;
}

// Function to compute the logarithm of a number to a given base
double logarithm(float x, float b) {
	return log(x) / log(b); // Using the natural log function from the math.h library
}