#include "philo.h"

void *routine(void *arg)
{

}

int main()
{
    int arr[]={2,3,5,7,11,13,17,19,23,29};

    pthread_t t[2];
    int i = 0;
    while (i < 2)
    {
        int *d = malloc();
        if(pthread_create(&t[i],NULL,&routine,i) != 0)
            perror("failed to create thread\n");
    }
    i = 0;
    while (i < 2)
    {
        if(pthread_join(t[i],NULL))
            perror("error joining the thread\n");
        i++;
    }
}