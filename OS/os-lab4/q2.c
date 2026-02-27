#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();
    if(pid==0) {
        for(int i=0; i<=100; i++) {
            printf("%d I am a child Process\n",i);
        }
    }
    else {
        for(int i=1; i<=100; i++) {
            printf("%d, I am a parent Process\n",i);
        }
    }
}