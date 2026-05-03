#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main() {
    const int SIZE = 4096;
    const char *name = "SHM_IPC";
    int fd;
    int *ptr;

    fd = shm_open(name, O_RDWR, 0666);
    ptr = (int*)mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    int sum = 0;
    printf("Consumer reading:   ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]);
        sum += ptr[i] * ptr[i];
    }
    printf("\nSum of squares: %d\n", sum);

    return 0;
}