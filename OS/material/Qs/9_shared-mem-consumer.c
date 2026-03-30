#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main() {
	const char *name = "OS";
	const int size = 4096;
	int fd;
	char* ptr;

	fd = shm_open(name,O_CREAT|O_RDWR,0666);
	ptr = (char*)mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("%s",(char*)ptr);
	shm_unlink(name);
}
