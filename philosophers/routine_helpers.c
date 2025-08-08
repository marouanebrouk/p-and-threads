#include "philosophers.h"




void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_died)
		printf("%lld %d %s\n", get_current_time_ms() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}





void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
}




static void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}




void	eat(t_philo *philo)
{
	take_forks(philo);
	print_action(philo, "is eating");

	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);

	// smart_sleep(philo->data->time_to_eat, philo->data);
	usleep(philo->data->time_to_eat * 1000);
	release_forks(philo);
}