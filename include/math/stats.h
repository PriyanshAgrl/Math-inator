#ifndef STATS_H
#define STATS_H

// Defining Max size of Datasets
#define MAX_CLI_ARGS 20 // Max Operands via command-line
#define MAX_DATASET_SIZE 100000 // Max elements via CSV file input (future) or CLI

// Statistics functions
double stats_mean(double arr[], int n);
double stats_median(double arr[], int n);
double stats_mode(double arr[], int n);
double stats_variance(double arr[], int n);
double stats_stddev(double arr[], int n);

#endif // STATS_H