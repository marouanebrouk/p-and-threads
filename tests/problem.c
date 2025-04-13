#include "philo.h"

void *routine(void * arg)
{
    int index = *(int *)arg;
    printf("%d\n",index);
}

int main()
{
int arr[] = {2,3,5,7,11,13,17,19,23,29};
    pthread_t t[10];
    int i = 0;
    while (i < 10)
    {
        if(pthread_create(&t[i],NULL,routine,(void *)&arr[i]) != 0)
            perror("failed to create thread\n");
        usleep(500);
        i++;
    }
    int j = 0;
    while(j < 10)
    {
            if(pthread_join(t[j],NULL) != 0)
                perror("failed to join thread\n");
            j++;
    }
    return 0;
}