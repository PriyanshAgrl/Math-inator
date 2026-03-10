#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "core/math_constants.h"
#include "math/stats.h"

static int compare(const void *a, const void *b)
{
    double fa = *(double*)a;
    double fb = *(double*)b;

    if (fa < fb) return -1;
    if (fa > fb) return 1;
    return 0;
}

double stats_mean(double arr[], int n) {
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	return sum / n;
}

double stats_median(double arr[], int n) {
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

double stats_mode(double arr[], int n) {
	// Need to explore the hash-map approach to reduce the time complexity
	// Need to improve code to handle multiple modes, like in dataset: [1, 1, 2, 2, 3, 3]
	int maxCount = 0;
	double mode_value = 0.0;
	for (int i = 0; i < n; i++) {
		int count = 0;
		for (int j = 0; j < n; j++) {
			if (fabs(arr[j] - arr[i]) < ZERO_TOLERANCE) { // Using a tolerance for floating-point comparison
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

double stats_variance(double arr[], int n) {
	double mean_value = stats_mean(arr, n);
	double variance = 0;
	for (int i = 0; i < n; i++) {
		variance += pow(arr[i] - mean_value, 2);
	}
	return variance / n;
}

double stats_stddev(double arr[], int n) {
	return sqrt(stats_variance(arr, n));
}