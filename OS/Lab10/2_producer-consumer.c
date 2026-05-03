#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define NUMPRODUCER 3
#define NUMCONSUMER 3
#define N 5

sem_t empty, full, mutex;
int buffer[N] = {0};
int in = 0, out = 0;
int orderID = 1;

void* producer(void* args) {
    int* id = (int*)args;
    while(1) {
        int order = orderID++;           

        sem_wait(&empty);                
        sem_wait(&mutex);

        buffer[in] = order;
        printf("Customer  %d placed  Order #%d at slot [%d]\n", *id, order, in);
        in = (in + 1) % N;

        sem_post(&mutex);
        sem_post(&full);                

        sleep(rand() % 2);              
    }
    free(id);
}

void* consumer(void* args) {
    int* id = (int*)args;
    while(1) {
        sem_wait(&full);                 
        sem_wait(&mutex);

        int order = buffer[out];
        printf("Agent     %d picked  Order #%d from slot [%d]\n", *id, order, out);
        out = (out + 1) % N;

        sem_post(&mutex);
        sem_post(&empty);              

        sleep(rand() % 3);              
    }
    free(id);
}

int main(int argc, int* argv[]) {
    sem_init(&empty, 0, N);
    sem_init(&full,  0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t producers[NUMPRODUCER];
    pthread_t consumers[NUMCONSUMER];

    for(int j = 0; j < NUMCONSUMER; j++) {
        int* id = (int*)malloc(sizeof(int));
        *id = j+1;
        pthread_create(&consumers[j], NULL, consumer, id);
    }
    for(int j = 0; j < NUMPRODUCER; j++) {
        int* id = (int*)malloc(sizeof(int));
        *id = j+1;
        pthread_create(&producers[j], NULL, producer, id);
    }
    for(int j = 0; j < NUMCONSUMER; j++)
        pthread_join(consumers[j], NULL);
    for(int j = 0; j < NUMPRODUCER; j++)
        pthread_join(producers[j], NULL);

    sem_destroy(&full);  sem_destroy(&empty);  sem_destroy(&mutex);
}