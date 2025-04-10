#include "philo.h"
pthread_mutex_t mutex;

void *ft_routine(void *arg)
{
    t_data *ddata;
    ddata = (t_data *)arg;
    long i = 0;
    while (i < 10000000)
    {
        pthread_mutex_lock(&mutex);
        ddata->number++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return (NULL);
}

int main()
{
    //stack code(local variable) vs heap code(pointers variables).
    pthread_mutex_init(&mutex,NULL);

    t_data *data;
    data = malloc(sizeof(t_data));
    pthread_t th[5];

    data->number = 42;
    data->name = "data";
    int j = 0;
    while (j < 5)
    {
        if (pthread_create(&th[j],NULL,ft_routine,(void *)data))
            {
                printf("failed to create threads");
                return (1);
            }
        printf("thread %d has started\n",j);
        j++;
    }
    j = 0;
    while (j < 5)
    {
        if (pthread_join(th[j],NULL) != 0)
            return (2);
            printf("thread %d has ended\n",j);
        j++;
    }
    pthread_mutex_destroy(&mutex);
    printf("%lld\n",data->number);
    free(data);
}