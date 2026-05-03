#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    fprintf(stdout, " Caught Signal %d", signum);
}

int main() {
    signal(SIGINT,sigint_handler);
    printf("Press Ctrl C to terminate\n");

    while(1) {
        sleep(1);
    }
    return 0;
}