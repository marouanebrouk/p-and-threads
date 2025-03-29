#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

void *ft_routine()
{
    printf("pid si %d\n",getpid());
    sleep(2);
    printf("bye thread\n");
}

int main()
{
    pthread_t t1,t2;
    if (pthread_create(&t1,NULL,&ft_routine,NULL) != 0)
    {
        return 1; // in case of error
    } //a way to protect the pthread_create function
    pthread_create(&t2,NULL,&ft_routine,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}