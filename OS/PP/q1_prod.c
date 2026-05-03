#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

int main() {
    const int SIZE = 4096;
    const char *name = "SHM_IPC";
    int fd;
    int *ptr;

    fd = shm_open(name, O_CREAT|O_RDWR, 0666);
    ftruncate(fd, SIZE);
    ptr = (int*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    srand(time(NULL));
    printf("Producer generating: ");
    for (int i = 0; i < 5; i++) {
        ptr[i] = rand() % 100;
        printf("%d ", ptr[i]);
    }
    printf("\n");

    sleep(2);  // give consumer time to read
    shm_unlink(name);
    return 0;
}