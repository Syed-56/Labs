#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argC, char *argV[]) {
    //S(N) = 1/2+1/4+...1/2N
    if(argC != 2){
        exit(1);
    }
    float n;
    n=atoi(argV[1]);
    if(n<=0 || n>=1000) {
        exit(1);
    }
    printf("Parent Inputs N\n");

    pid_t pid = fork();
    if (pid<0) {
        fprintf(stderr,"Fork Failed");
        exit(1);
    }

    if(pid==0) {    //child
        printf("Child Process now performs Summation\n");
        float sum=0;
        for (int i=2; i<=(2*n); i+=2) {
            sum += 1.00/(1.0*i);
        }
        printf("Sum: %.2f\n", sum);
    } else { 
        printf("Back in Parent Process\n");
        wait(NULL);
    }
}