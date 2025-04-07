#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"

void *my_routine(void *arg)
{
    printf("thread 1\n");
    sleep(2);
    printf("end thread 1\n");
}

void *my_routine2(void *arg)
{
    printf("thread 2\n");
    sleep(2);
    printf("end thread 2");
}

int main()
{
    pthread_t t1;
    if(pthread_create(&t1, NULL, my_routine, NULL) != 0)
        return (1);
    if(pthread_join(t1,NULL))
        return (2);
}