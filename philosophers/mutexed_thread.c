#include "philo.h"

int var = 0;
pthread_mutex_t mutex;

void *routine(void *arg)
{
    int i = 0;
    while (i < 10000000)
    {
        pthread_mutex_lock(&mutex);
        var++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main()
{
    pthread_t t1,t2;
    pthread_mutex_init(&mutex,NULL);
    
    pthread_create(&t1,NULL,&routine,NULL);
    pthread_create(&t2,NULL,&routine,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);
    printf("%d\n",var);
}
