#include "philo.h"

pthread_mutex_t mutex;

void *routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i = 0;
    while (i < 10000000)
    {
        pthread_mutex_lock(&mutex);
        data->number++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
}

int main()
{
    t_data mero;
    mero.name = "marouane";
    mero.number = 0;
    
    pthread_t t1,t2;
    pthread_mutex_init(&mutex,NULL);
    
    pthread_create(&t1,NULL,&routine,(void *)&mero);
    pthread_create(&t2,NULL,&routine,(void *)&mero);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_mutex_destroy(&mutex);
    printf("%d\n",mero.number);
}
