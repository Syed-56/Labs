#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function that the thread will execute
void *threadFunction(void *arg) {
    printf("Thread is running and doing some work...\n");
    sleep(2); // Simulate work
    printf("Thread work finished and exiting.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;
    int create_result = pthread_create(&thread, NULL, threadFunction, NULL);
    if (create_result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // Detach the thread so resources are automatically cleaned up 
    int detach_result = pthread_detach(thread);
    if (detach_result != 0) {
        fprintf(stderr, "Error detaching thread\n");
    } else {
        printf("Thread detached successfully. It will clean up itself.\n");
    }

    printf("Main thread continues execution...\n");
    sleep(3);
    printf("Main thread exiting.\n");
    return 0;
}