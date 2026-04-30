#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("Inside Parent Process\n");
    pid_t pid1 = fork();     //1 child is created
    if(pid1==0) {
        printf("In Child Process 1. PID=%d and Parent PID=%d\n", getpid(), getppid());
        exit(0);    //exit doesnt immediately delete all records of this process, exit status is inside process table. Since its termintaed, its in zombie state
    }
    
    pid_t pid2 = fork();    //2 child is created
     if(pid2==0) {
        printf("In Child Process 2. PID=%d and Parent PID=%d\n", getpid(), getppid());
        exit(0);    //same concept as above, now due to this the parent might starts executing before its finished so we wait
    }
    int status;
    wait(&status);
    printf("Now back in Parent Process\n");
}