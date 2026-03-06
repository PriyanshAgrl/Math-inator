// Future Update: Add the features to perform unit conversion, stats functions, simplification of expressions, solution of simple algebra and many more. 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "arithmetic.h"
#include "trigo.h"
#include "stats.h"
#include "history.h"

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
						float arr[MAX_DATASET_SIZE];
						int n;
						do {
							// Asking the user for the number of elements
							printf("Enter the number of elements (upto %d): ", MAX_DATASET_SIZE);
							scanf("%d", &n);
							if (n <= 0 || n > MAX_DATASET_SIZE) {
								printf("Error: Invalid input. Please enter a valid number.\n");
							}
						} while (n <= 0 || n > MAX_DATASET_SIZE);
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