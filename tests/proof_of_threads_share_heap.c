#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_shared {
    char *msg;
} t_shared;

void *thread1(void *arg)
{
    t_shared *data = (t_shared *)arg;

    data->msg = malloc(100);
    if (!data->msg)
        return NULL;

    sprintf(data->msg, "Hello from thread 1 (allocated on heap)!");
    return NULL;
}

void *thread2(void *arg)
{
    t_shared *data = (t_shared *)arg;

    // Wait for thread1 to allocate and write
    sleep(1);

    printf("Thread 2 read: %s\n", data->msg);

    return NULL;
}

int main()
{
    pthread_t t1, t2;
    t_shared shared_data;
    shared_data.msg = NULL;

    pthread_create(&t1, NULL, thread1, &shared_data);
    pthread_create(&t2, NULL, thread2, &shared_data);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    free(shared_data.msg);
    return 0;
}
