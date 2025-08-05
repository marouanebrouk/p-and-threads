#include "philosophers.h"

int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meals_counter_mutex, NULL) != 0)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}




int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->philo_nb)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;

		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_nb];

		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}



int	init_all(t_data *data, int argc, char **argv)
{
	data->philo_nb = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->meals_nb = -1;
	if (argc == 6)
		data->meals_nb = ft_atoi(argv[5]);
	data->someone_died = 0;
	data->start_time = gtime_ms();
	if (init_mutexes(data))
		return (write(2,"Mutex initialization failed\n",28));
	if (init_philos(data))
		return (write(2,"Philo init failed\n",18), 1);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meals_counter_mutex);
	free(data->forks);
	free(data->philos);
}


int main(int ac, char **av)
{
	t_data data;
	if(!ft_is_valid_args(ac, av));
		return (1);
	if(init_all(&data, ac,av))
		return (1);
	// start_simulation()
	cleanup(&data);
	return (0);
}