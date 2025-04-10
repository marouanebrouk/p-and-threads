#include "philo.h"

int arr[] = {2,3,5,7,11,13,17,19,23,29};

pthread_mutex_t mutex;

void *routine(void * arg)
{
    int index = *(int *)arg;
    // pthread_mutex_lock(&mutex);
    printf("%d\n",arr[index]);
    // pthread_mutex_unlock(&mutex);
    return(NULL);
}


int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_t t[10];
    for (int i = 0; i < 10; i++)
    {
        if(pthread_create(&t[i],NULL,routine,(void *)&i) != 0)
            perror("failed to create thread\n");
        usleep(500);
    }

    for (int j = 0; j < 10; j++)
    {
            if(pthread_join(t[j],NULL) != 0)
                perror("failed to join thread\n");
    }
    return 0;
    pthread_mutex_destroy(&mutex);
}