#ifndef STATS_H
#define STATS_H

// Defining Max size of Dataset
#define MAX_DATASET_SIZE 100

int compare(const void *a, const void *b); // Array Sorting function for qsort
double stats(float arr[], int n, int subChoice); // Statistics functions

#endif