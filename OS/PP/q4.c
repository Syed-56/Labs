#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define FILENAME "shared_data.txt"

sem_t data_ready;

void *writer(void *arg) {
    FILE *f = fopen(FILENAME, "w");
    if (!f) { perror("fopen"); pthread_exit(NULL); }

    fprintf(f, "Hello from Writer: OS Lab Final Exam\n");
    fclose(f);
    printf("Writer: data written.\n");

    sem_post(&data_ready);
    pthread_exit(NULL);
}

void *reader(void *arg) {
    sem_wait(&data_ready);

    FILE *f = fopen(FILENAME, "r");
    if (!f) { perror("fopen"); pthread_exit(NULL); }

    char buf[256];
    printf("Reader: reading file:\n");
    while (fgets(buf, sizeof(buf), f))
        printf("  %s", buf);

    fclose(f);
    pthread_exit(NULL);
}

int main() {
    sem_init(&data_ready, 0, 0);

    pthread_t wt, rt;
    pthread_create(&wt, NULL, writer, NULL);
    pthread_create(&rt, NULL, reader, NULL);

    pthread_join(wt, NULL);
    pthread_join(rt, NULL);

    sem_destroy(&data_ready);
    return 0;
}