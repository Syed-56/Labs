#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>

void proc_wait() {
    int wstat;
    pid_t pid;
    while ((pid = waitpid(-1,&wstat,WNOHANG))>0) {        
        printf("Return Code: %d\n", wstat);
    }
}

int main() {
    signal(SIGCHLD, proc_wait);
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Child %d started\n", getpid());
            sleep(2);
            printf("Child %d exiting\n", getpid());
            exit(0);
        }
    }
    sleep(10);
    printf("Parent exiting\n");
    return 0;
}
