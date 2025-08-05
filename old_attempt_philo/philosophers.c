#include "philosophers.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lld %d %s\n", timestamp(), philo->id, action);
	pthread_mutex_unlock(&philo->data->print);
}

long long	timestamp(void)
{
	struct timeval	tv;
	long long		ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (ms);
}


int	ft_init_data(t_data *data, int ac, char **av)
{
	int	i;

	i = -1;
	data->philo_nb = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meals_nb = -1;
	if (ac == 6)
		data->meals_nb = ft_atoi(av[5]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		return (0);
    while (++i < data->philo_nb)
    {
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		return (0);
    }
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (0);
	return (1);
}






int	ft_init_philosophers(t_data *data)
{
	int	i;
	
	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (0);
	while (++i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nb];
		data->philos[i].data = data;
	}
	return (1);
}











void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42)
	{
		print_action(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_action(philo, "is sleeping");
		usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}