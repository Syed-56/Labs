#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

int main() {
	const int size = 4096;
	const char* name = "OS";
	char msg[256];
	int fd;	char *ptr;

	fd = shm_open(name,O_CREAT|O_RDWR,0666);
	ftruncate(fd,size);
	ptr = (char*)mmap(0,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	printf("Enter Message: ");
	while(1) {
		fgets(msg,sizeof(msg),stdin);
		if(strcmp(msg,"exit\n")==0) break;
		sprintf(ptr,"%s",msg);
		ptr += strlen(msg);
	}
}
