#include <stdio.h>
#include "cli/history.h"

// Function to display the history of the last 5 calculations
void displayHistory(double result, double history[], int *hCount) {
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
    printf("%g\t", history[i]);
  }
  printf("\n");
}