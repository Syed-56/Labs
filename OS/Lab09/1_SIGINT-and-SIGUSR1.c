#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

void signalhandler(int signum) {
    fprintf(stdout, "Caugh SIGINT signal: %d", signum);
    fprintf(stdout, "Raise SIGKILL ");
    raise(SIGKILL);
}

void my_handler(int signum) {
    fprintf(stdout, "Caught SIGUSR1 signal: %d", signum);
}

int main() {
    if(signal(SIGINT,signalhandler)==SIG_ERR)
        printf("Error\n");
    if(signal(SIGUSR1,my_handler)==SIG_ERR)
        printf("Error\n");

    printf("Press Ctrl C to terminate\n");
    pid_t pid = getpid();
    sleep(3);
    printf("Kill SIGUSR1");
    kill(pid,SIGUSR1);

    while(1)
        sleep(1);
}