#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 100

// Global variable to store min and max values
int min_value, max_value;

int main() {
    // Array of 100 elements
    int array[SIZE];

    // Seed for random number generation
    srand(time(NULL));

    // Populate the array with random numbers
    #pragma omp parallel for
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 100; // Random number between 0 and 99
        // Print the generated number and thread number (optional)
        printf("Thread %d placed %d in the array\n", omp_get_thread_num(), array[i]);
    }

    // Reduction to find the minimum value
    #pragma omp parallel for reduction(min:min_value)
    for (int i = 0; i < SIZE; i++) {
        // Initialize min_value to a large number
        if (i == 0) {
            min_value = array[i];  // Set first element as initial min
        }
        // Update min_value if a smaller element is found
        if (array[i] < min_value) {
            min_value = array[i];
        }
    }

    // Print the minimum value
    printf("Minimum value: %d\n", min_value);

    // Reduction to find the maximum value
    #pragma omp parallel for reduction(max:max_value)
    for (int i = 0; i < SIZE; i++) {
        // Initialize max_value to a small number
        if (i == 0) {
            max_value = array[i];  // Set first element as initial max
        }
        // Update max_value if a larger element is found
        if (array[i] > max_value) {
            max_value = array[i];
        }
    }

    int sum = 0;

    // Print the maximum value
    printf("Maximum value: %d\n", max_value);

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < SIZE; i++) {
        sum += array[i];  // Accumulate sum of array elements
    }

double average = (double)sum / SIZE;  // Compute the average

    // Print the average value
    printf("Average value: %.2f\n", average);

    return 0;
}

