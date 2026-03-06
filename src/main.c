// Future Update: Add the features to perform unit conversion, stats functions, simplification of expressions, solution of simple algebra and many more. 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Defining Precision Tolerance
#define EPSILON 1e-6
// Defining Max size of Dataset
#define MAX_SIZE 100
// Defining maximum history size
#define MAX_HISTORY 5 

// Function Declaration Prototypes
double add(float x, float y);      // Adds two numbers and returns the result
double subtract(float x, float y); // Subtracts y from x and returns the result
double product(float x, float y);  // Multiplies two numbers and returns the result
double divide(float x, float y);   // Divides x by y and returns the result
int rem(int x, int y);             // Calculates the remainder of x divided by y
double sqroot(float x);            // Computes the square root of x
double power(float x, float y);    // Raises x to the power of y
int fact(int x);                   // Calculates the factorial of x
double logarithm(float x, float b);   // Log of (x) to the base b
double trigo(float x, int r); 		 // Trigonometric functions
int compare(const void *a, const void *b); // Array Sorting function for qsort
double stats(float arr[], int n, int subChoice); // Statistics functions

void displayHistory(double result, float history[], int *hCount); // Displays the recent history of results

int main(void) {
  // Greeting the user!
  printf("Welcome to the Awesome Math-inator!!\n");
  //  Displaying the available operations
  printf("\nAvailabe operations:\n");
  printf("1. Addition (+)\n");
  printf("2. Subtraction (-)\n");
  printf("3. Multiplication (*)\n");
  printf("4. Division (/)\n");
  printf("5. Modulo (%%)\n");
  printf("6. Square Root (√ )\n");
  printf("7. Power (^)\n");
  printf("8. Factorial (!)\n");
  printf("9. Logarithm (log)\n");
  printf("10. Trigonometry\n");
  printf("11. Statistics\n");
  printf("0. Exit\n");
  
  // Declaring variables
  int choice;     // User's choice for the operation
	int subChoice;		// User's choice for Sub Menus
  float a, b;     // Input numbers for calculations
	int numscanned; // Input Validation
  double result;  // Result of the mathematical operation
  char repeat;    // User's choice to restart for another calculation
  float history[MAX_HISTORY];  // Array to store history
  int hCount = 0;        // Counter for history array
  
  // Main loop for user interactions
  do {
    // Prompting user for choice
    printf("\nEnter your choice (0 - 11) : ");
    scanf(" %d", &choice);
		
    // Switch statement to handle different user choices
    switch (choice) {
      // Case 1: Addition
      case 1: {
        do {
          printf("Enter first number: ");
          numscanned = scanf(" %f", &a);
          if (numscanned != 1) {
            printf("Error: Invalid input. Please enter a valid number.\n");
          }
        } while (numscanned != 1);
        do {
          printf("Enter second number: ");
          numscanned = scanf(" %f", &b);
          if (numscanned != 1) {
            printf("Error: Invalid input. Please enter a valid number.\n");
          }
        } while (numscanned != 1);

        result = add(a, b);
        printf("Result : %g + %g = %g\n", a, b, result);
        break;
      }
      // Case 2: Subtraction
      case 2: {
				do {
					printf("Enter first number: ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
				do {
					printf("Enter second number: ");
					numscanned = scanf(" %f", &b);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = subtract(a, b);
        printf("Result : %g - %g = %g\n", a, b, result);
        break;
      }
      // Case 3: Multiplication
      case 3: {
				do {
					printf("Enter first number: ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
				do {
					printf("Enter second number: ");
					numscanned = scanf(" %f", &b);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = product(a, b);
        printf("Result : %g * %g = %g\n", a, b, result);
        break;
      }
      // Case 4: Division
      case 4: {
				do {
					printf("Enter first number: ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
				do {
					printf("Enter second number: ");
					numscanned = scanf(" %f", &b);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = divide(a, b);
        if (!isnan(result)) {
          printf("Result : %g / %g = %g\n", a, b, result);
        }
        break;
      }
      // Case 5: Modulo
      case 5: {
				do {
					printf("Enter first number: ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
				do {
					printf("Enter second number: ");
					numscanned = scanf(" %f", &b);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = rem((int)a, (int)b);
        printf("Result : %d %% %d = %d\n", (int)a, (int)b, (int)result);
        break;
      }
      // Case 6: Square Root
      case 6: {
				do {
					printf("Enter a number: ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf(" Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = sqroot(a);
        if (!isnan(result)) {
          printf("Result : √%g = %g\n", a, result);
        }
        break;
      }
      // Case 7: Exponentiation
      case 7: {
				do {
					printf("Enter first number (base): ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
				do {
					printf("Enter second number (exponent): ");
					numscanned = scanf(" %f", &b);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = power(a, b);
        printf("Result : %g ^ %g = %g\n", a, b, result); // I can use %e for scientific notation but %g is more visually appealing
        break;
      }
      // Case 8: Factorial
      case 8: {
				do {
					printf("Enter a number: ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1 || (int)a != a) {
						printf("Error: Invalid input. Please enter a positive integer.\n");
						break;
					}
				} while (numscanned != 1 || (int)a != a);
        result = fact(a);
        if (!isnan(result)) {
          printf("Result : %d! = %g\n", (int)a, result);
        }
        break;
      }
      // Case 9: Logarithm
      case 9: {
				do {
					printf("Enter first number (argument): ");
					numscanned = scanf(" %f", &a);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
				do {
					printf("Enter second number (base): ");
					numscanned = scanf(" %f", &b);
					if (numscanned != 1) {
						printf("Error: Invalid input. Please enter a valid number.\n");
					}
				} while (numscanned != 1);
        result = logarithm(a, b);
        printf("Result : Log (%g) to base %g = %g\n", a, b, result);
        break;
      }
			// Case 10: Trigonometry
      case 10: {
				//  Displaying the available trigometric functions
				printf("\nAvailable Trigonometric Functions:\n");
				printf("1. Sine (sin)\n");
				printf("2. Cosine (cos)\n");
				printf("3. Tangent (tan)\n");
				printf("4. Cotangent (cot)\n");
				printf("5. Secant (sec)\n");
				printf("6. Cosecant (cosec)\n");
				printf("0. Back to main menu\n");
				// Prompting user for choice
				printf("\nEnter your choice (0 - 6) : ");
				scanf(" %d", &subChoice);
				if (subChoice == 0) {
					// go back to main menu 
					break;
				} else if (subChoice >= 1 && subChoice <= 6) {
					do {
						printf("Enter the angle (in degrees): ");
						numscanned = scanf("%f", &a);
						if (numscanned == 1) {
							result = trigo(a, subChoice);
							if (!isnan(result)) { // Checking if result is not 'NaN'
								printf("%s ( %g ) = %g\n", subChoice == 1 ? "sin" : subChoice == 2 ? "cos" : subChoice == 3 ? "tan" : subChoice == 4 ? "cot" : subChoice == 5 ? "sec" : subChoice == 6 ? "cosec" : "Invalid function", a, result);
								// Using ternary operator to display function name for conciseness, even though switch case was better option for readability.
							}
						} else {
							printf("Error: Invalid input. Please enter a valid angle.\n");
						}
					} while (numscanned != 1); // Loop until valid (number) input is entered
				} else {
					printf("Error: Invalid choice. Please Enter a digit from 0 to 6.\n");
				}
				break;
			}
			// Case 11: Statistics
			case 11: {
				//  Displaying the available statistical operations
				printf("\nAvailable Statistical Operations (for univariate samples only):\n");
				printf("1. Arithmetic Mean\n");
				printf("2. Median\n");
				printf("3. Mode\n");
				printf("4. Variance\n");
				printf("5. Standard Deviation\n");
				printf("0. Back to main menu\n");
				// Prompting user for choice
				printf("\nEnter your choice (0 - 5) : ");
				scanf(" %d", &subChoice);
				if (subChoice == 0) {
					// go back to main menu 
					break;
				} else if (subChoice >= 1 && subChoice <= 5) {
					do {
						float arr[MAX_SIZE];
						int n;
						do {
							// Asking the user for the number of elements
							printf("Enter the number of elements (upto %d): ", MAX_SIZE);
							scanf("%d", &n);
							if (n <= 0 || n > MAX_SIZE) {
								printf("Error: Invalid input. Please enter a valid number.\n");
							}
						} while (n <= 0 || n > MAX_SIZE);
						// Prompt the user to enter the elements of the array
						printf("Enter the elements of the dataset:\n");
						for (int i = 0; i < n; i++) {
							numscanned = scanf(" %f", &arr[i]);
						}
						if (numscanned == 1) {
							result = stats(arr, n, subChoice);
							if (!isnan(result)) { // Checking if result is not 'NaN'
								printf("%s of the given dataset = %g\n", subChoice == 1 ? "Mean" : subChoice == 2 ? "Median" : subChoice == 3 ? "Mode" : subChoice == 4 ? "Variance" : subChoice == 5 ? "Standard Deviation" : "Invalid function", result);
								// Using ternary operator to display function name for conciseness, even though switch case was better option for readability.
							}
						} else {
							printf("Error: Invalid input. Please enter valid data.\n");
						}
					} while (numscanned != 1); // Loop until valid samples are entered
				} else {
					printf("Error: Invalid choice. Please Enter a digit from 0 to 6.\n");
				}
				break;
			}
      // Case 0: Exit option
      case 0: {
        break;
      }
      // Default case for invalid choice
      default: {
        printf("Invalid choice. Please Enter a digit from 0 to 10.\n");
        break;
      }
    }
    printf("\n------------------------------------------------");

    // Displaying the history of the last 5 calculations
    displayHistory(result, &history[MAX_HISTORY], &hCount);
    printf("------------------------------------------------\n");
    
    // Asking the user if they wanna Restart
    printf("\nAh, behold! Another chance for mathematical brilliance? (Type 'y' for genius or 'n' for... well, not genius): ");
    scanf(" %c", &repeat);
    
  } while (repeat == 'y');
	
  // Displaying a thank you message at the end
  if (repeat == 'n') {
    printf("\nCurse you, mundane calculations! Until next time, then.\nThank you for using the Awesome Math-inator!!\n");
  }
	
  return 0; // Return 0 for successful execution
}

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

// Function to calculate the values of trigonometric functions
double trigo(float x, int r) {
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

int compare(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

// Fuction to Calculate the values of statistical Operations (Central Tendency & Dispersion)
double stats(float arr[], int n, int subChoice) {
	switch(subChoice) {
		case 1: {
			double sum = 0;
			for (int i = 0; i < n; i++) {
				sum += arr[i];
			}
			return sum / n;
		}
		case 2: {
			// Sorting the Array
			qsort(arr, n, sizeof(float), compare);
			// If the number of element is odd, returning the middle element
			if (n % 2 != 0) {
				return arr[n / 2];
			}
			// If the number of element is even, returning the average of the middle two elements
			else {
				return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
			}
		}
		case 3: {
			// Need to explore the hash-map approach to reduce the time complexity
			// Need to improve code to handle multiple modes, like in dataset: [1, 1, 2, 2, 3, 3]
			int maxCount = 0;
			float mode_value = 0;
			for (int i = 0; i < n; i++) {
				int count = 0;
				for (int j = 0; j < n; j++) {
					if (arr[j] == arr[i]) {
						count++;
					}
				}
				if (count > maxCount) {
					maxCount = count;
					mode_value = arr[i];
				}
			}
			return mode_value;
		}
		case 4: {
			double mean_value = stats(arr, n, 1);
			double variance = 0;
			for (int i = 0; i < n; i++) {
				variance += pow(arr[i] - mean_value, 2);
			}
			return variance / n;
		}
		case 5: {
			return sqrt(stats(arr, n, 4));
		}
		default:
			printf("Invalid statistical function choice.\n");
			return NAN;  // Default return value when no case matches
	}
}

// Function to display the history of the last 5 calculations
void displayHistory(double result, float history[], int *hCount) {
  // Checking for available space before Inserting result to history array
  if (*hCount < MAX_HISTORY) {
    history[*hCount] = result;
    (*hCount)++;
  } else {
    // Shifting values to accommodate new result, if history is full
    for (int i = 0; i < MAX_HISTORY - 1; i++) {
      history[i] = history[i + 1];
    }
		// Adding the new result to the end of the history array
    history[MAX_HISTORY - 1] = result;
  }

  // Displaying the history
  printf("\nMini-History (last %d results): ", MAX_HISTORY);

  // Displaying the last 'history count' results
  for (int i = *hCount - 1; i >= 0; i--) {
    printf("%g,\t", history[i]);
  }
  printf("\n");
}