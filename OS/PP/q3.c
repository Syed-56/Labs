#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define FLOORS 4
#define SPOTS  20
#define CARS   100

int floor_spots[FLOORS];
pthread_mutex_t floor_mutex[FLOORS];
sem_t payment_sem;

void *car_thread(void *arg) {
    int car_id = *(int*)arg;
    int floor = rand() % FLOORS;

    while (1) {
        pthread_mutex_lock(&floor_mutex[floor]);
        if (floor_spots[floor] > 0) {
            floor_spots[floor]--;
            pthread_mutex_unlock(&floor_mutex[floor]);
            break;
        }
        pthread_mutex_unlock(&floor_mutex[floor]);
        floor = (floor + 1) % FLOORS;
    }

    usleep((rand() % 300 + 100) * 1000);

    sem_wait(&payment_sem);
    printf("Car %d paying (floor %d)\n", car_id, floor);
    usleep(50000);
    sem_post(&payment_sem);

    pthread_mutex_lock(&floor_mutex[floor]);
    floor_spots[floor]++;
    pthread_mutex_unlock(&floor_mutex[floor]);

    pthread_exit(0);
}

int main() {
    srand(time(NULL));
    sem_init(&payment_sem, 0, 1);

    for (int i = 0; i < FLOORS; i++) {
        floor_spots[i] = SPOTS;
        pthread_mutex_init(&floor_mutex[i], NULL);
    }

    pthread_t cars[CARS];
    int ids[CARS];
    for (int i = 0; i < CARS; i++) {
        ids[i] = i + 1;
        pthread_create(&cars[i], NULL, car_thread, &ids[i]);
    }
    for (int i = 0; i < CARS; i++)
        pthread_join(cars[i], NULL);

    printf("All %d cars processed.\n", CARS);
    sem_destroy(&payment_sem);
    for (int i = 0; i < FLOORS; i++)
        pthread_mutex_destroy(&floor_mutex[i]);
    return 0;
}