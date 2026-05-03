//DINING PHILOSPHERS'S: 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t mutex;               
sem_t S[N];                

int state[N];              

#define THINKING 0
#define HUNGRY 1
#define EATING 2

// Helper functions
int LEFT(int i) { return (i + N - 1) % N; }
int RIGHT(int i) { return (i + 1) % N; }

// Try to pick up chopsticks
void test(int i) {
    if (state[i] == HUNGRY &&
        state[LEFT(i)] != EATING &&
        state[RIGHT(i)] != EATING) {

        state[i] = EATING;
        printf("Philosopher %d is EATING\n", i);
        sem_post(&S[i]);   // allow philosopher to eat
    }
}

// Pick forks/chopstick
void take_forks(int i) {
    sem_wait(&mutex);

    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", i);

    test(i);  // check if can eat

    sem_post(&mutex);

    sem_wait(&S[i]);  // wait if not allowed
}

// Put down chopsticks
void put_forks(int i) {
    sem_wait(&mutex);

    state[i] = THINKING;
    printf("Philosopher %d is THINKING\n", i);

    // check if neighbors can eat now
    test(LEFT(i));
    test(RIGHT(i));

    sem_post(&mutex);
}

// Philosopher thread
void* philosopher(void* num) {
    int i = *(int*)num;

    while (1) {
        printf("Philosopher %d is THINKING\n", i);
        sleep(1);

        take_forks(i);

        sleep(2); // eating

        put_forks(i);
    }
}

int main() {
    pthread_t thread_id[N];
    int phil[N];

    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (int i = 0; i < N; i++) {
        phil[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}