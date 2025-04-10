#include "philo.h"

int var = 0;
pthread_mutex_t mutex;

void* child_fn (void* arg){
   pthread_mutex_lock(&mutex);
   var++;
   pthread_mutex_unlock(&mutex);
   return NULL;
}
int main ( void ) {
   pthread_t child;
   pthread_mutex_init(&mutex,NULL);
   pthread_create(&child, NULL, child_fn, NULL);
   pthread_join(child, NULL);
   pthread_mutex_destroy(&mutex);
   printf ("%d\n", var);
   return 0;
}