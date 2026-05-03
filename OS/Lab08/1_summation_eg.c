#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int sum=0;

void *runner(void *num) {
    int limit = *(int*)num;
    int i;
    if (limit>0) {
        for(int i=1; i<=limit; i++)
        sum += i;
    }
    pthread_exit((void*)404);
}

int main(int argc, char* argv[]) {
    pthread_t thread_id;
    pthread_attr_t attributes;
    int num=10;

    pthread_create(&thread_id,NULL,runner,(void*)&num);
    void *exit_status;
    pthread_join(thread_id,&exit_status);
    printf("PThread exited with Status: %ld\n", (long)exit_status);
    printf("Sum: %d\n", sum);
}