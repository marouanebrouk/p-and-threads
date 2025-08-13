#include "philosophers.h"


void	ft_sleep(long duration, t_data *data)
{
	long	start;

	start = get_current_time_ms();
	while (!did_someone_die(data) && (get_current_time_ms() - start) < duration)
		usleep(200);
}

void ft_think(t_philo *philo)
{
    print_action(philo, "is thinking");
    if (philo->data->philo_nb % 2 && philo->data->time_to_eat >= philo->data->time_to_sleep)
        usleep(philo->data->time_to_eat * 1000);
    else
        usleep(1000);
}

void deal_with_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo,"has taken a fork");
	usleep(1000 * philo->data->time_to_die);
	print_action(philo,"is died");
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nb == 1)
		deal_with_one_philo(philo);
	while (!did_someone_die(philo->data) && philo->data->philo_nb != 1)
	{
		if (philo->id % 2 == 0)
			usleep(500);
		ft_think(philo);
		usleep(1000 );
		if(eat(philo))
			return(NULL);
		print_action(philo, "is sleeping");
		// ft_sleep(philo->data->time_to_sleep, philo->data);
		if (philo->data->time_to_sleep > philo->data->time_to_die)
			usleep(philo->data->time_to_die * 1000);
		else
			usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

int	check_death(t_philo *philo)
{
	long	current_time;

	current_time = get_current_time_ms();
	pthread_mutex_lock(&philo->meal_lock);
	if (current_time - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->print);
		if (!did_someone_die(philo->data))
		{
			printf("%lld %d died\n", current_time - philo->data->start_time, philo->id);
			pthread_mutex_lock(&philo->data->someone_mutex);
			philo->data->someone_died = 1;
			pthread_mutex_unlock(&philo->data->someone_mutex);
		}
		pthread_mutex_unlock(&philo->data->print);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

int	check_if_all_ate(t_data *data)
{
	int	i;
	int	full_philo;

	i = 0;
	full_philo = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->meals_nb)
			full_philo++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (full_philo >= data->philo_nb)
	{
		pthread_mutex_lock(&data->someone_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->someone_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (!did_someone_die(data))
	{
		i = 0;
		while (i < data->philo_nb)
		{
			if (check_death(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (data->meals_nb != -1 && check_if_all_ate(data))
			return (NULL);
		usleep(500);
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
	if (data->philo_nb > 1)
	{
		if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		{
			write(2,"monitor thread creation failed\n", 31);
			return (1);
		}
		pthread_join(monitor, NULL); // wail till end of simulation
	}
	return (0);
}
