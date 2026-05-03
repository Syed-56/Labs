#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main() {
    int size = 4096;
    const char* name = "OS";
    const char* msg = "Hello";
    int fd = shm_open(name,O_CREAT|O_RDWR,0666);
    ftruncate(fd,size);
    char *ptr =  (char*)mmap(0,fd,PROT_READ|PROT_WRITE,MAP_SHARED,size,0);
    sprintf(ptr,"%s",0);
    ptr += strlen(msg);
    sleep(10.0);
    return;
}
