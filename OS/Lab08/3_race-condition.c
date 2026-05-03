#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
long count=0;

void* counter(void* str) {
    printf("Executing Thread %s\n", (char*)str);
    for (long i=0; i<10e7; i++) {
        count++;
    }
    pthread_exit(0);
}

int main(int argc, char* argv[]) {
    pthread_t t1,t2;
    pthread_create(&t1, NULL, counter, "A");
    pthread_create(&t2, NULL, counter, "B");
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Both Threads Executed: Counter=%ld\n", count);
}