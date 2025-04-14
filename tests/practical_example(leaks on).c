#include "philo.h"
int arr[]={2,3,5,7,11,13,17,19,23,29};
int gsum = 0;
// pthread_mutex_t mutex;

void *routine(void *arg)
{
    int i = 0;
    int  sum = 0;
    int index = *(int *)arg;
    while (i < 5)
    {
        // pthread_mutex_lock(&mutex);
        sum = sum + arr[(index) + i];
        i++;
        // pthread_mutex_unlock(&mutex);
    }
    printf("local sum is %d\n",sum);
    *(int *)arg = sum;
    return (arg);
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
        printf("thread %d -------------\n",i+1);
        i++;
        sleep(1);
    }
    i = 0;
    while (i < 2)
    {
        if(pthread_join(t[i],(void **)&res))
            perror("error joining the thread\n");
        i++;
        gsum += *res;
        // printf("gsum is %d\n",gsum);
    }
    printf("%d\n",gsum);
}