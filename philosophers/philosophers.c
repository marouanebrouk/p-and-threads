#include "philosophers.h"


void	ft_sleep(long duration, t_data *data)
{
	long	start;

	start = get_current_time_ms();
	while (!data->someone_died && (get_current_time_ms() - start) < duration)
		usleep(100); // check every 100us
}



void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100); // sleep even to enhance synchro

	while (!philo->data->someone_died)
	{
		eat(philo);
		print_action(philo, "is sleeping");
		// ft_sleep(philo->data->time_to_sleep, philo->data);
		usleep(philo->data->time_to_sleep * 1000);
		print_action(philo, "is thinking");
	}
	return (NULL);
}







int	check_death(t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->meal_lock);
	current_time = get_current_time_ms();
	if (current_time - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print);
		if (!philo->data->someone_died)
		{
			printf("%lld %d died\n", current_time - philo->data->start_time, philo->id);
			philo->data->someone_died = 1;
		}
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}


int	check_all_ate(t_data *data)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	pthread_mutex_lock(&data->meals_counter_mutex);
	while (i < data->philo_nb)
	{
		if (data->philos[i].meals_eaten >= data->meals_nb)
			full_count++;
		i++;
	}
	pthread_mutex_unlock(&data->meals_counter_mutex);
	if (full_count == data->philo_nb)
	{
		pthread_mutex_lock(&data->print);
		data->someone_died = 1; // use same flag to stop everything
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}





void	*monitor_routine(void *arg)
{
	t_data	*data = (t_data *)arg;
	int		i;

	while (!data->someone_died)
	{
		i = 0;
		while (i < data->philo_nb)
		{
			if (check_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (data->meals_nb != -1 && check_all_ate(data))
			return (NULL);
		usleep(1000); // avoid busy waiting
	}
	return (NULL);
}












int	thread_creation(t_data *data)
{
	int	i;
	pthread_t monitor;
	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
		{
			write(2,"thread creation failed\n", 23);
			while (--i >= 0)
				pthread_detach(data->philos[i].thread);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		write(2,"monitor thread creation failed\n", 31);
		return (1);
	}
	pthread_join(monitor, NULL); // wait until simulation ends
	return (0);
}
