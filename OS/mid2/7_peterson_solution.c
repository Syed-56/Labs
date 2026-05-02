//Petersons Solution
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

bool flag[2] = {false, false};
int turn;

void* process0(void* arg) {
    while (1) {
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1);

        printf("Process 0 in critical section\n");

        flag[0] = false;
    }
}

void* process1(void* arg) {
    while (1) {
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0);

        printf("Process 1 in critical section\n");

        flag[1] = false;
    }
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, process0, NULL);
    pthread_create(&t2, NULL, process1, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}