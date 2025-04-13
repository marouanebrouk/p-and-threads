#include "philo.h"
pthread_mutex_t mutex;

void *ft_routine(void *arg)
{
    t_data *ddata;
    ddata = (t_data *)arg;
    long i = 0;
    while (i < 100000)
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
pthread_mutex_init(&mutex,NULL);

t_data data;
// data = malloc(sizeof(t_data));
pthread_t t1,t2;

data.number = 0;
data.name = "marouane";
pthread_create(&t1,NULL,ft_routine,(void *)&data);
pthread_create(&t2,NULL,ft_routine,(void *)&data);

pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_mutex_destroy(&mutex);
printf("%lld\n",data.number);
printf("%s\n",data.name);
}