#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void sigusr1_handler(int signum) {
    printf("Parent process received the signal.\n");
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    pid_t pid = fork();

    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {
        for (int i = 0; i < 3; i++) {
            sleep(1);
            kill(getppid(), SIGUSR1);
            printf("Child sent SIGUSR1 (#%d)\n", i+1);
        }
        exit(0);
    } else {
        printf("Parent process is waiting for the signal.\n");
        pause();
        wait(NULL);
    }
    return 0;
}