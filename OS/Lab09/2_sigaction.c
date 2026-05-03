#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighandler(int signum) {
    printf("SigInt Recieved: %d", signum);
    exit(signum);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = sighandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT,&sa,NULL);
    while(1){}
    return EXIT_SUCCESS;
}