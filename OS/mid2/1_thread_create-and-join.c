#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
// Thread function
void *helloWorld(void *vargp) {
    sleep(1);
    printf("Hello World\n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    printf("Before Thread\n");
    // Creating the thread
    pthread_create(&thread_id, NULL, helloWorld, NULL);
    // Waiting for the thread to finish
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    exit(0);
}