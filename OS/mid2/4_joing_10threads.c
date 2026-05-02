#define NUM_THREADS 10
#include <pthread.h>

/* an array of threads to be joined upon */
int main() {
    pthread_t workers [NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    pthread_join(workers[i], NULL);
}