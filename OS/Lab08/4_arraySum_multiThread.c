#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAYSIZE 1000
#define NUMTHREADS 4
int arr[ARRAYSIZE];

void* sumArr(void* arg) {
    int threadNum = *(int*)arg;
    int start = threadNum*(ARRAYSIZE/NUMTHREADS);
    int end = start + (ARRAYSIZE/NUMTHREADS);
    long sum=0;

    for(int i=start; i<=end; i++) {
        sum += arr[i];
    }
    pthread_exit((void*)sum);
}

int main(int argC, char* argV[]) {
    pthread_t threads[NUMTHREADS];
    int threadArgs[NUMTHREADS];
    void* threadResults[NUMTHREADS];
    long totalSum=0;
    for(int i=0; i<ARRAYSIZE; i++)
        arr[i] = i;

    for(int i=0; i<NUMTHREADS; i++) {
        threadArgs[i]=i;
        pthread_create(&threads[i],NULL,sumArr,&threadArgs[i]);
    }
    for(int i=0; i<NUMTHREADS; i++) {
        pthread_join(threads[i], &threadResults[i]);
        totalSum += (long)threadResults[i];
    }
    printf("Total Sum: %ld\n", totalSum);
}