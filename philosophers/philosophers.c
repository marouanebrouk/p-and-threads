/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrouk <mbrouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:27:52 by mbrouk            #+#    #+#             */
/*   Updated: 2025/08/16 17:31:02 by mbrouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(long duration, t_data *data)
{
	long	start;

	start = get_current_time_ms();
	while (!did_someone_die(data) && (get_current_time_ms() - start) < duration)
		usleep(200);
}

void	deal_with_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	usleep(1000 * philo->data->time_to_die);
	print_action(philo, "is died");
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_nb == 1)
		deal_with_one_philo(philo);
	if (philo->id % 2 == 0)
		usleep(1000 * 20);
	while (!did_someone_die(philo->data) && philo->data->philo_nb != 1)
	{
		if (eat(philo))
			return (NULL);
		print_action(philo, "is sleeping");
		ft_sleep(philo->data->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
		ft_think(philo);
	}
	return (NULL);
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
		usleep(100);
	}
	return (NULL);
}

int	thread_creation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->philo_nb)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]))
		{
			write(2, "thread creation failed\n", 23);
			while (--i >= 0)
				pthread_join(data->philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	if (data->philo_nb > 1)
	{
		pthread_create(&monitor, NULL, monitor_routine, data);
		pthread_join(monitor, NULL);
	}
	return (0);
}
