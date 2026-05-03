//READER WRITER:
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int read_count = 0;

// Reader function
void* reader(void* arg) {
    int id = *(int*)arg;

    while (1) {
        // Entry section
        sem_wait(&mutex);
        read_count++;

        if (read_count == 1)
            sem_wait(&wrt);   // first reader blocks writers

        sem_post(&mutex);

        // Critical section
        printf("Reader %d is READING\n", id);
        sleep(1);

        // Exit section
        sem_wait(&mutex);
        read_count--;

        if (read_count == 0)
            sem_post(&wrt);   // last reader allows writer

        sem_post(&mutex);

        sleep(1);
    }
}

// Writer function
void* writer(void* arg) {
    int id = *(int*)arg;

    while (1) {
        sem_wait(&wrt);   // request exclusive access

        // Critical section
        printf("Writer %d is WRITING\n", id);
        sleep(2);

        sem_post(&wrt);   // release resource

        sleep(1);
    }
}

int main() {
    pthread_t r[5], w[2];
    int i, id[5];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create readers
    for (i = 0; i < 5; i++) {
        id[i] = i;
        pthread_create(&r[i], NULL, reader, &id[i]);
    }

    // Create writers
    for (i = 0; i < 2; i++) {
        id[i] = i;
        pthread_create(&w[i], NULL, writer, &id[i]);
    }

    for (i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    for (i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    return 0;
}