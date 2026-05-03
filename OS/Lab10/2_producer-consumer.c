#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMPRODUCER 5
#define NUMCONSUMER 8
#define N 8

sem_t empty,full,mutex;
int buffer[N] = {0};
int i=0, j=0;

void* producer(void* args) {
    int* id = (int*)args;
    while(1) {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[i] = *id;
        printf("Producer inserted %d at buffer %d\n", *id, i);
        i=(i+1)%N;
        sem_post(&mutex);
        sem_post(&full);
        sleep(2);
    }
    free(id);
}

void* consumer(void* args) {
    int id;
    while(1) {
       sem_wait(&full);
       sem_wait(&mutex);
       id = buffer[j];
       printf("Consumer consumed %d at buffer %d\n", id, j);
       j=(j+1)%N;
       sem_post(&mutex);
       sem_post(&empty); 
    }
}

int main(int argc, int* argv[]) {
    sem_init(&empty,0,N);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    pthread_t producers[NUMPRODUCER];
    pthread_t consumers[NUMCONSUMER];

    for(int j=0; j<NUMCONSUMER; j++) {
        pthread_create(&consumers[j],NULL,consumer,NULL);
    }
    for(int j=0; j<NUMPRODUCER; j++) {
        int *id = (int*)malloc(sizeof(int));
        *id=j;
        pthread_create(&producers[j],NULL,producer,id);
    }

    for(int j=0; j<NUMCONSUMER; j++)
        pthread_join(consumers[j],NULL);
    for(int j=0; j<NUMPRODUCER; j++)
        pthread_join(producers[j],NULL);
    
    sem_destroy(&full); sem_destroy(&empty);  sem_destroy(&mutex);
}
