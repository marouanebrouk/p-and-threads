#include "philo.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void *roll_dice()
{
    int value = (rand() % 10) + 1;
    int *result ;
    *result = value;
    printf("%d\n",*result);
    return ((void *)result);
}

int main()
{
    srand(time(0));
    pthread_t t1;
    int *res;

    if (pthread_create(&t1,NULL,&roll_dice,NULL) != 0)
        return (1);
    if(pthread_join(t1,(void**)&res) != 0)
        return (3);

    printf("%d\n",*res);
    // printf("%p\n",res);
    // free(res);
}
