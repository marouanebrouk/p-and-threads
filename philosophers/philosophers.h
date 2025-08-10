#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
#include <stdio.h>


typedef struct s_data t_data;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    int             meals_eaten;
    long long       last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_lock;
    t_data         *data;
}   t_philo;

typedef struct s_data
{
    int             philo_nb;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meals_nb;
    int             someone_died;
    long long       start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print;
    pthread_mutex_t someone_mutex;
    pthread_mutex_t meals_counter_mutex;
    t_philo         *philos;
}   t_data;

int     ft_isnot_valid_args(int ac, char **av);
int	ft_init_data(t_data *data, int ac, char **av);
int ft_atoi(char *str);
int	ft_init_philosophers(t_data *data);
void	*ft_routine(void *arg);

void	print_action(t_philo *philo, char *action);
long long	get_current_time_ms(void);

void	cleanup(t_data *data);
int	init_all(t_data *data, int argc, char **argv);
int	init_philos(t_data *data);
int	init_mutexes(t_data *data);
int thread_creation(t_data * data);
void	print_action(t_philo *philo, char *msg);
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
int	check_death(t_philo *philo);
int	check_all_ate(t_data *data);
void	*monitor_routine(void *arg);
void	release_forks(t_philo *philo);


#endif
