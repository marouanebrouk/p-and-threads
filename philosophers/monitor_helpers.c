/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrouk <mbrouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:29:55 by mbrouk            #+#    #+#             */
/*   Updated: 2025/08/16 18:04:07 by mbrouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_think(t_philo *philo)
{
	if (philo->data->philo_nb % 2 != 0
		&& philo->data->time_to_eat >= philo->data->time_to_sleep)
		usleep(philo->data->time_to_eat * 1000);
	else
		usleep(1000 * 5);
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
			printf("%lld %d died\n", current_time - philo->data->start_time,
				philo->id);
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
