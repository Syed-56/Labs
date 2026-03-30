#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    const int SIZE = 4096;  //size of shared memory object
    const char *name = "OS";    //name of shared memory object
    const char *msg0 = "Hello"; 
    const char *msg1 = "World\n";
    int fd; //shared memory file descriptor
    char *ptr;  //ptr to shared memory

    fd = shm_open(name, O_CREAT|O_RDWR, 0666);  //create object
    ftruncate(fd,SIZE); //configure size of shared memory object
    ptr = (char*)mmap(0,SIZE,PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);
    sprintf(ptr,"%s",msg0);
    ptr += strlen(msg0);    //in memory we wrote the hello where ptr was pointing now increment ptr by that distance to write further without overwrite
    sprintf(ptr,"%s",msg1);
    ptr += strlen(msg1);
    sleep(10.0);

    return 0;
}