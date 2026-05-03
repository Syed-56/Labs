#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define READERS 5
#define WRITERS 2
int readCount=0;
sem_t mutex, wrt;

void *reader(void* arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&mutex);
        readCount++;
        if(readCount==1)
            sem_wait(&wrt);
        sem_post(&mutex);

        printf("Reader %d reads\n", id);
        sleep(1);

        sem_wait(&mutex);
        readCount--;
        if(readCount==0)
            sem_post(&wrt);
        sem_post(&mutex);
        sleep(1);
    }
}

void *writer(void* arg) {
    int id = *(int*)arg;
    while(1) {
        sem_wait(&wrt);
        printf("Writer %d writes\n", id);
        sleep(1);
        sem_post(&wrt);
    }
}

int main(int argc, char* argv) {
    int id[READERS];
    pthread_t r[READERS];
    pthread_t w[WRITERS];
    sem_init(&mutex,0,1);
    sem_init(&wrt,0,1);

    for(int i=0; i<READERS; i++) {
        id[i]=i;
        pthread_create(&r[i],NULL,reader,&id[i]);
    }
    for(int i=0; i<WRITERS; i++) {
        id[i]=i;
        pthread_create(&w[i],NULL,writer,&id[i]);
    }

    for(int i=0; i<READERS; i++) {
        pthread_join(r[i],NULL);
    }
    for(int i=0; i<WRITERS; i++) {
        pthread_join(w[i],NULL);
    }

    sem_destroy(&mutex);    sem_destroy(&wrt);
}