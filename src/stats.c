#include <stdio.h>
#include <math.h>
#include "stats.h"

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