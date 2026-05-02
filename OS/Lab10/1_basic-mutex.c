#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

int shared_data = 0;
pthread_mutex_t mutex;

void *thread_function(void *arg) {
    int thread_id = *((int *)arg);

    // Lock and unlock the mutex around shared resources
    pthread_mutex_lock(&mutex);
    shared_data++;                          // Critical section - Thread is accessing shared_data
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int       thread_args[NUM_THREADS];
    int i;

    pthread_mutex_init(&mutex, NULL);       // Initialize the mutex

    for (i = 0; i < NUM_THREADS; i++) {     // Create threads
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }
    for (i = 0; i < NUM_THREADS; i++)       // Join threads
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);          // Destroy the mutex

    return 0;
}