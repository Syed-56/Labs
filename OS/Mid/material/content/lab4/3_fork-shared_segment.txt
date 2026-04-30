#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int sharerVar=100;  //this code segment is shared across all process.
    printf("Shared Variable Before fork = %d\n", sharerVar);

    pid_t pid=fork();
    if(pid<0) {
        fprintf(stderr,"Fork Failed\n");
        return 1;
    }
    else if(pid==0) {
        sharerVar=200;  //its a seperate copy so modification dont affect shared value
        printf("I am child (PID=%d) where shared variables = %d\n", getpid(),sharerVar);  
    }
    else {
        //parent
        printf("I am Parent (PID=%d) where original value is kept, so shared variable = %d\n",getpid(), sharerVar);
    }

}