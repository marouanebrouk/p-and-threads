#include "philosophers.h"


typedef struct s_sdata
{
    int value;
}  t_sdata;

pthread_mutex_t mutex;

void *routine(void *arg)
{
    t_sdata *data2 = (t_sdata *)arg;
    int i = 0;
    while (i < 100)
    {
        data2->value++;
        i++;
    }
    return (NULL);
}

int main()
{
    t_sdata data;
    pthread_t t1,t2;

    data.value = 
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1,NULL,routine,(void *)&data);
    pthread_create(&t2,NULL,routine,(void *)&data);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("data is %d\n",data.value);
    pthread_mutex_destroy(&mutex);
}