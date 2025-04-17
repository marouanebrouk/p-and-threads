#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


typedef struct s_philo
{
    int time_to_die;
    int time_to_eat;
} t_philo;

typedef struct s_conditions
{
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
}t_condition;


int ft_atoi(char *str);


#endif