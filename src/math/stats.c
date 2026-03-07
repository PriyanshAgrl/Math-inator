#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "math/stats.h"

int compare(const void *a, const void *b)
{
    double fa = *(double*)a;
    double fb = *(double*)b;

    if (fa < fb) return -1;
    if (fa > fb) return 1;
    return 0;
}

// Fuction to Calculate the values of statistical Operations (Central Tendency & Dispersion)
double stats(double arr[], int n, int subChoice) {
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
			qsort(arr, n, sizeof(double), compare);
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