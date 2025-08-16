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
    while (i < 1000)
    {
        pthread_mutex_lock(&mutex);
        data2->value++;
        pthread_mutex_unlock(&mutex);
        i++;
    }
    return (NULL);
}

void *routine2(void *arg)
{
    sleep(1);
    t_sdata *s1 = (t_sdata *)arg;
    if (s1)
    {
        printf("hello from s1 %d \n",s1->value);
        free(s1);
    }
    return (NULL);
}

int main()
{
    t_sdata *data;
    data = malloc(sizeof(t_sdata));
    pthread_t t1,t2,t3;

    data->value = 42;
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&t1,NULL,routine,(void *)data);
    pthread_create(&t2,NULL,routine,(void *)data);
    // sleep(2);
    pthread_create(&t3,NULL,routine2,(void *)data);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    printf("data is %d\n",data->value);
    pthread_mutex_destroy(&mutex);
}