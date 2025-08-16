#include "philosophers.h"



int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo_nb > 0)
	{
		data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
		if (!data->forks)
			return (1);
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->someone_mutex, NULL);
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}



int	init_philos(t_data *data)
{
	int	i;

	if (data->philo_nb > 0)
	{
		data->philos = malloc(sizeof(t_philo) * data->philo_nb);
		if (!data->philos)
			return (1);
	}
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nb];
		pthread_mutex_init(&data->philos[i].meal_lock, NULL);
		i++;
	}
	return (0);
}


int init_data(t_data *data, int argc, char **argv)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_nb = -1;
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) == 0)
			return (write(2,"Argument 6 need to be more than 0\n",35),1);
		data->meals_nb = ft_atoi(argv[5]);
	}
	data->someone_died = 0;
	data->start_time = get_current_time_ms();
	return 0;
}
