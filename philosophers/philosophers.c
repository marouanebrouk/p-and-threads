#include "philosophers.h"



void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->rules->print);
	printf("%lld %d %s\n", timestamp(), philo->id, action);
	pthread_mutex_unlock(&philo->rules->print);
}

long long	timestamp(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}




int	ft_init_rules(t_rules *rules, int ac, char **av)
{
	int	i;
	
	i = -1;
	rules->philo_nb = ft_atoi(av[1]);
	rules->time_to_die = ft_atoi(av[2]);
	rules->time_to_eat = ft_atoi(av[3]);
	rules->time_to_sleep = ft_atoi(av[4]);
	rules->meals_nb = -1;
	if (ac == 6)
	rules->meals_nb = ft_atoi(av[5]);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->philo_nb);
	if (!rules->forks)
	return (0);
    while (++i < rules->philo_nb)
    {
		if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
		return (0);
    }
	if (pthread_mutex_init(&rules->print, NULL) != 0)
		return (0);
	return (1);
}


int	ft_init_philosophers(t_rules *rules)
{
	int	i;
	
	i = -1;
	rules->philos = malloc(sizeof(t_philo) * rules->philo_nb);
	if (!rules->philos)
		return (0);
	while (++i < rules->philo_nb)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].left_fork = &rules->forks[i];
		rules->philos[i].right_fork = &rules->forks[(i + 1) % rules->philo_nb];
		rules->philos[i].rules = rules;
	}
	return (1);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1337)
	{
		
		print_action(philo, "is thinking");

		
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");

		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");

		print_action(philo, "is eating");
		usleep(philo->rules->time_to_eat * 1000);


		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		
		print_action(philo, "is sleeping");
		usleep(philo->rules->time_to_sleep * 1000);
	}
	return (NULL);
}