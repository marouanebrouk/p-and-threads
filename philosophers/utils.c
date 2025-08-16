/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrouk <mbrouk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:15:47 by mbrouk            #+#    #+#             */
/*   Updated: 2025/08/16 17:15:53 by mbrouk           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_current_time_ms(void)
{
	struct timeval	tv;
	long long		time_now;

	time_now = 0;
	gettimeofday(&tv, NULL);
	time_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time_now);
}

int	did_someone_die(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->someone_mutex);
	ret = data->someone_died;
	pthread_mutex_unlock(&data->someone_mutex);
	return (ret);
}
