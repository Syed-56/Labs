#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
	
	pid_t pid = fork();
	if(pid<0) {
		printf("Error");
		exit(1);
	}
	else if(pid==0) {
		printf("\nChild...\n");
		execlp("mkdir","mkdir", "Test-Dir",NULL);
		exit(0);
	}
	else {
		wait(NULL);
		printf("\nParent\n");
		execlp("ls","ls",NULL);
		exit(0);
	}
}
