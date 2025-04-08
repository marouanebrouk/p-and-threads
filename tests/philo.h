#ifndef PHILO_H
# define PHILO_H

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "unistd.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


typedef struct s_data
{
    long long number;
    char *name;
} t_data;

#endif