#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigint_handler(int signum) {
    char response;

    fprintf(stdout, "\nInterrupt signal received! (Signal %d)\n", signum);
    fprintf(stdout, "Do you really want to exit? (Y/N): ");

    response = getchar();

    if (response == 'Y' || response == 'y') {
        printf("Exiting program. Goodbye!\n");
        exit(0);
    } else {
        printf("Resuming program...\n");
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    printf("Press Ctrl+C to terminate\n");

    while (1) {
        sleep(1);
    }

    return 0;
}