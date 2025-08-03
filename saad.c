#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>
#include <stdlib.h>


// atomic_read();

pthread_mutex_t mutex;

void *ft_routine(void *arg)
{
    int *b = (int *)arg;
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex);
        (*b)++;
        pthread_mutex_unlock(&mutex);
    }
    // exit(1);
    printf("alskhdlasjd\n");
    exit(1);
    return (NULL);
}


// void *ft_r2()
// {

// }

int main()
{
    pthread_t t1, t2;

    int a = 0;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&t1, NULL, &ft_routine,(void *)&a);
    pthread_create(&t2, NULL, &ft_routine,(void *)&a);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("a is %d \n",a);
    pthread_mutex_destroy(&mutex);
}