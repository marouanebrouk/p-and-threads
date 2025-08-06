#include "philosophers.h"




void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	// pthread_mutex_lock(&philo->data->print);
	printf("Philo %d is thinking\n", philo->id);
	// pthread_mutex_unlock(&philo->data->print);
	// usleep(100*1000);
	return (NULL);
}

int	thread_creation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
		{
			write(2,"thread creation failed\n", 23);
			while (--i >= 0)
				pthread_detach(data->philos[i].thread);
			return (1);
		}
		i++;
	}
	return (0);
}
