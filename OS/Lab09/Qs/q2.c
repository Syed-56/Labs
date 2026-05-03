#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

int running = 1;

void sigusr1_handler(int signum) {
    printf("Signal received in thread!\n");
    running = 0;
}

void *printer_thread(void *arg) {
    while (running) {
        printf("Thread running...\n");
        sleep(1);
    }
    return NULL;
}

void *signal_thread(void *arg) {
    signal(SIGUSR1, sigusr1_handler);
    pause();
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, printer_thread, NULL);
    pthread_create(&t2, NULL, signal_thread, NULL);

    printf("PID = %d  |  Run: kill -SIGUSR1 %d\n\n", getpid(), getpid());

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Program terminated gracefully.\n");
    return 0;
}