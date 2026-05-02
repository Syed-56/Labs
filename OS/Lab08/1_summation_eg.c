#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0; // this data is shared by the thread(s)
void *runner(void *parameters)
{ // The thread will begin control in this funtion
    int i, upper = *((int *)parameters);
    if (upper > 0)
    {
        for (i = 1; i <= upper; i++)
        sum = sum + i;
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t threadID; // thread identifier
    pthread_attr_t attributes; // set attributes for the thread
    int num = 1000;

    pthread_attr_init(&attributes); // get the default attributes
    pthread_create(&threadID, &attributes, runner, (void *)&num); // create the threa
    pthread_join(threadID, NULL); // now wait for the thread to exit
    printf("sum=%d\n", sum);
    exit(0);
}