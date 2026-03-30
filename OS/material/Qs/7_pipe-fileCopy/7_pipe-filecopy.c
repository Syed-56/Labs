#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argC, char *argV[]) {
	if(argC != 3) {
		printf("Invalid Argument");
		exit(1);
	}

	int pipefd[2];	//0 for READ and 1 for WRITE
	pipe(pipefd);
	pid_t pid = fork();
	if(pid<0) {
		printf("Error");
		exit(1);
	}
	else if(pid==0) {
		//child
		close(pipefd[1]);
		int dest = open(argV[2],O_WRONLY|O_CREAT,0666);
		char buffer[1024];
		int bytesRead;
		//read
		while((bytesRead = read(pipefd[0], buffer, sizeof(buffer)))>0) {
			write(dest,buffer,bytesRead);
		}
		close(pipefd[0]);
		close(dest);
	}
	else {
		//parent
		close(pipefd[0]);
		int src = open(argV[1], O_RDONLY);
		char buffer[1024];
		int bytesRead;
		//write
		while((bytesRead=read(src,buffer,sizeof(buffer)))>0) {
			write(pipefd[1],buffer,bytesRead);
		}
		close(pipefd[1]);
		close(src);
		wait(NULL);
	}
	return 0;
}
