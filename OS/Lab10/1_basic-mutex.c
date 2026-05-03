#include <stdio.h>
#include <pthread.h>
int shared = 0;
pthread_mutex_t mutex;
#define NUMTHREADS 4

void* runner(void* arg) {
    int threadID = *(int*)arg;
    pthread_mutex_lock(&mutex);
    shared++;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main(int argc, char* argV) {
    pthread_t threads[NUMTHREADS];
    int threadArgs[NUMTHREADS];
    pthread_mutex_init(&mutex,NULL);

    for(int i=0; i<NUMTHREADS; i++) {
        threadArgs[i] = i;
        pthread_create(&threads[i],NULL,runner,&threadArgs[i]);
    }
    for(int i=0; i<NUMTHREADS; i++) {
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
}