#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
int sum=0;

void *runner(void *num) {
    int limit = *(int*)num;
    int i;
    if (limit>0) {
        for(int i=1; i<=limit; i++)
        sum += i;
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    pthread_t thread_id;
    pthread_attr_t attributes;
    int num=10;

    pthread_attr_init(&attributes);
    pthread_attr_setdetachstate(&attributes,PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_id,&attributes,runner,(void*)&num);
    pthread_attr_destroy(&attributes);
    sleep(1);
    printf("Sum: %d\n", sum);
}