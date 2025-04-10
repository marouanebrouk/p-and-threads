#include "philo.h"

int arr[] = {2,3,5,7,11,13,17,19,23,29};

void *routine(void * arg)
{
    int *i = (int *)arg;
    printf("%d\n",arr[*i]);
    sleep(1);
    return(NULL);
}


int main()
{
    pthread_t t[10];
     int i = 0;
    while (i < 10)
    {
        if(pthread_create(t + i,NULL,routine,(void *)&i) != 0)
            perror("failed to create thread");
        i++;
    }

    for (int j = 0; j < 10; j++)
    {
            if(pthread_join(t[j],NULL) != 0)
            return (1);
    }
    return 0;
}