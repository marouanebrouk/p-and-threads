// #include <stdio.h>
// int main()
// {
//     int num = 123;
//     int mod = 0,s=0;
//     int T[8]= {0,2,4,8,16,32,64,128};
//     int i = 0;
//     char arr[8];
//     while (i < 8)
//     {
//         mod = num % 2;
//         arr[i] = mod;
//         num = num / 2;
//         i++;
//     }
//     while (--i >= 0)
//     {
//         if(arr[i] == 1){
//             s+=T[i];
//         }
//         printf("%d",arr[i]);
//     }
//     printf("\n%d\n",s);
// }

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#define BIG 1000000000UL

typedef  struct s_utils
{
    uint32_t a;
    pthread_mutex_t mutex;
} t_utils;


void *change_a(void *arg)
{
 uint32_t *a = (uint32_t *)arg;
 for(uint32_t i = 0; i < BIG; i++)
 {
     pthread_mutex_lock(&mutex);
     (*a)++;
     pthread_mutex_unlock(mutex);
 }
 return (NULL);
}

int main()
{
 pthread_t thread_1;
 pthread_t thread_2;
 uint32_t a;

 a = 0;
 pthread_create(&thread_1, NULL, change_a, &a);
 pthread_create(&thread_2, NULL, change_a, &a);
 pthread_join(thread_1, NULL);
 pthread_join(thread_2, NULL);
 printf("a is: %u\n", a);
}