#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sigterm_handler(int signum) {
    printf("Child terminated by parent\n");
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        signal(SIGTERM, sigterm_handler);
        while (1) {
            printf("Child process running...\n");
            sleep(1);
        }
    } else {
        // Parent process
        printf("Parent waiting 5 seconds...\n");
        sleep(5);
        printf("Parent sending SIGTERM to child (PID=%d)\n", pid);
        kill(pid, SIGTERM);
        wait(NULL);
        printf("Parent: child has terminated.\n");
    }

    return 0;
}