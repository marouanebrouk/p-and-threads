#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

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
    int             nb_philo;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_required;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    t_philo         *philos;
}   t_rules;

int     ft_is_valid_args(int ac, char **av);
int	ft_init_rules(t_rules *rules, int ac, char **av);
int ft_atoi(char *str);
int	ft_init_philosophers(t_rules *rules);
void	*ft_routine(void *arg);



#endif