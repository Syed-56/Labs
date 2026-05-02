#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 1000000 // Adjusted for cleaner division

int global_array[ARRAY_SIZE]; 

// Function to initialize the array with random values
void initialize_array() {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        global_array[i] = rand() % 100;
    }
}

// Function to find the sum of elements in a portion of the array
void *sum_array(void *arg) {
    int thread_id = *((int *)arg);
    int start = thread_id * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);
    long sum = 0; // Use long to prevent overflow

    for (int i = start; i < end; ++i) {
        sum += global_array[i];
    }
    return (void *)sum; 
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    void *thread_results[NUM_THREADS];
    long total_sum = 0;
    initialize_array();

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_args[i] = i;
        if (pthread_create(&threads[i], NULL, sum_array, (void *)&thread_args[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // Join threads and collect results
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &thread_results[i]);
        total_sum += (long)thread_results[i]; 
    }
    printf("Total sum of array elements: %ld\n", total_sum);
    return 0;
}