#include "philosophers.h"

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
	// pthread_mutex_destroy(&data->someone);
	free(data->forks);
	free(data->philos);
}