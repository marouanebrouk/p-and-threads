#include "philosophers.h"
#include "stdatomic.h"

typedef struct w_data
{
    _Atomic int value;
    pthread_mutex_t mutex;
} tw_data;


void *routine(void *arg)
{
    tw_data *data2 = (tw_data *)arg;
    // printf("value is %d \n",data2->value);

    for (int i = 0; i < 1000000;i++)
    {
        // pthread_mutex_lock(&data2->mutex);
        data2->value++;
        // pthread_mutex_unlock(&data2->mutex);
    }
    return (NULL);
}

int main()
{
    tw_data data;
    data.value = 2;
    pthread_mutex_init(&data.mutex,NULL);
    pthread_t t1 , t2;
    pthread_create(&t1,NULL,&routine,(void *)&data);
    pthread_create(&t2,NULL,&routine,(void *)&data);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("data.value is %d \n",data.value);
    pthread_mutex_destroy(&data.mutex);
}