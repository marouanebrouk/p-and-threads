#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// # include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
#include <stdio.h>


typedef struct s_rules t_rules;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_rules         *rules;
}   t_philo;

typedef struct s_rules
{
    int             philo_nb;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_nb;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t meals_to_eat;
    t_philo         *philos;
}   t_rules;
int     ft_is_valid_args(int ac, char **av);
int	ft_init_rules(t_rules *rules, int ac, char **av);
int ft_atoi(char *str);
int	ft_init_philosophers(t_rules *rules);
void	*ft_routine(void *arg);


void	print_action(t_philo *philo, char *action);
long long	timestamp(void);



#endif
