#include "philo.h"


void *my_thread(void *arg)
{
    t_data *data = (t_data *)arg;
    printf("pid si %d\n",getpid());
    sleep(2);
    printf("bye %d thread\n",data->number);
    printf("bye %s thread\n",(*data).name);
}

int main()
{
    pthread_t t1, t2;
    t_data data;
    data.number = 100;
    data.name = "marouane";
    
    if (pthread_create(&t1,NULL,&my_thread,(void *)&data) != 0)
        return 1;
    if (pthread_create(&t2,NULL,&my_thread,(void *)&data) != 0)
        return 2;
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
}