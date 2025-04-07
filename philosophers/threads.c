#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "pthread.h"

typedef struct f_threads
{
    int number;
    char *name;
} t_threads;

void *my_thread(void *arg)
{
    t_threads *data = (t_threads *)arg;
    printf("pid si %d\n",getpid());
    printf("pid si %lld\n",pthread_self());
    sleep(2);
    printf("bye %d thread\n",data->number);
    printf("bye %s thread\n",(*data).name);
}

int main()
{
    pthread_t t1, t2;
    t_threads data;
    data.number = 100;
    data.name = "marouane";
    
    if (pthread_create(&t1,NULL,&my_thread,(void *)&data) != 0)
        return 1;
    if (pthread_create(&t2,NULL,&my_thread,(void *)&data) != 0)
        return 2;
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}