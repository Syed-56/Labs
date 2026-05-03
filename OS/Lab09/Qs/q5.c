#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int signum) {
    printf("User-defined signal 1 received\n");
}

void sigusr2_handler(int signum) {
    printf("User-defined signal 2 received\n");
}

int main() {
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);

    printf("PID = %d\n", getpid());
    printf("Send: kill -SIGUSR1 %d\n", getpid());
    printf("Send: kill -SIGUSR2 %d\n\n", getpid());

    while (1) {
        pause();
    }

    return 0;
}