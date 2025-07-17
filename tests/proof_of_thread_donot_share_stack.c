#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// This will hold a pointer to thread1's local variable
int *illegal_pointer = NULL;

void *thread1(void *arg)
{
    int local = 42;
    illegal_pointer = &local;  // Save address of local (stack) variable
    printf("Thread 1 local: %d (address: %p)\n", local, (void *)&local);
    sleep(2);  // Keep thread1 alive to not destroy the stack frame yet
    return NULL;
}

void *thread2(void *arg)
{
    sleep(3);  // Wait until thread1 has returned
    printf("Thread 2 trying to read from thread1's local: %d (address: %p)\n",
           *illegal_pointer, (void *)illegal_pointer);
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
