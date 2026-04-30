#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int fd[2];  //1 for write end and 1 for read
    pid_t pid;
    printf("Enter Input MSG: ");
    fgets(write_msg,BUFFER_SIZE,stdin);

    if(pipe(fd)==-1) {  //create a pipe
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    pid = fork();   //create child
    sleep(10.0);
    if(pid<0) { //error
        fprintf(stderr, "Pipe Failed");
        return 1;
    }
    else if(pid>0) { //parent process
        close(fd[READ_END]);
        write(fd[WRITE_END], write_msg, strlen(write_msg)+1);   //writing the msg for which we pass file descriptor and the msg along with its length
        close(fd[WRITE_END]);
    }
    else {  //child Process
        close(fd[WRITE_END]);
        read(fd[READ_END], read_msg, BUFFER_SIZE);  //read the msg by passing fd of read along with msg and buffer size
        printf("read %s", read_msg);    //output the read msg
        close(fd[READ_END]);
    }
    return 0;
}