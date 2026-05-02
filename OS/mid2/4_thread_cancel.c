#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *arg) {
    printf("Worker thread: Started. Entering an infinite loop...\n");
    
    // Threads check for cancellation at certain points (like sleep or printf)
    while (1) {
        printf("Worker thread: Still running...\n");
        sleep(1); 
    }   
    return NULL;
}

int main() {
    pthread_t tid;
    // Create the worker thread
    if (pthread_create(&tid, NULL, worker, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }
    // Let the thread run for a few seconds
    sleep(3);
    /* Send a cancellation request to the thread */
    printf("Main thread: Sending cancellation request...\n");
    pthread_cancel(tid);
    /* Joining is recommended to clean up resources */
    pthread_join(tid, NULL);
    printf("Main thread: Worker thread has been canceled and joined.\n");
    return 0;
}