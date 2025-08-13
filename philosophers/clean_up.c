#include "philosophers.h"

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	if (data->philo_nb > 0)
	{
		while (i < data->philo_nb)
		{
			pthread_mutex_destroy(&data->forks[i]);
			// pthread_mutex_destroy(&data->philos[i].meal_lock);
			pthread_mutex_destroy(&data->philos[i].meal_time_lock);
			i++;
		}
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->someone_mutex);
		if (data->forks)
			free(data->forks);
		if (data->philos)
			free(data->philos);
	}
	free(data);
}