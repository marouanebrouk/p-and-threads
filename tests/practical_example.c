#include "philo.h"
int arr[]={2,3,5,7,11,13,17,19,23,29};

void *routine(void *arg)
{
    int i = 0;
    int *sum = malloc(sizeof(int));
    int *index = (int *)arg;
    while (i < 5)
    {
        *sum = *sum + arr[(*index) + i];
        i++;
    }
    free(index);
    return (sum);
}

int main()
{
    pthread_t t[2];
    int i = 0;
    int *res;
    while (i < 2)
    {
        int *d = malloc(sizeof(int));
        *d = (i * 5);
        if(pthread_create(&t[i],NULL,&routine,(void *)d) != 0)
            perror("failed to create thread\n");
        i++;
    }
    i = 0;
    while (i < 2)
    {
        if(pthread_join(t[i],(void **)&res))
            perror("error joining the thread\n");
        i++;
    }
    printf("%d\n",*res);
    free(res);
}