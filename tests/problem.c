#include "philo.h"
int arr[]={2,3,5,7,11,13,17,19,23,29};

void *routine(void *arg)
{
    int *d = (int *)arg;
    printf("%d\n",arr[*d]);
    free(d);
    return (NULL);
}

int main()
{

    pthread_t t[10];
    int i = 0;
    while (i < 10)
    {
        int *d = malloc(sizeof(int));
        *d = i;
        if (pthread_create(&t[i],NULL,&routine,(void *)d) != 0)
            perror("failed to create thread\n");
        usleep(100000);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        if (pthread_join(t[i],NULL) != 0)
            perror("failed to join thread");
        i++;
    }
}