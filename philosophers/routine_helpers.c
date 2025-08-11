#include "philosophers.h"



void	print_action(t_philo *philo, char *msg)
{
	long long passed_time;

	passed_time = get_current_time_ms() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->someone_died)
		printf("%lld %d %s\n", passed_time ,philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}


// void	take_forks(t_philo *philo)
// {
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(philo->right_fork);
// 		print_action(philo, "has taken a fork");
// 		pthread_mutex_lock(philo->left_fork);
// 		print_action(philo, "has taken a fork");
// 	}
// }




void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	if (philo->data->someone_died)
	{
		return (pthread_mutex_unlock(philo->left_fork));
	}
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->someone_died)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_current_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	// smart_sleep(philo->data->time_to_eat, philo->data);
	if (philo->data->time_to_eat > philo->data->time_to_die) // this if condition is for (10 400 100000000 100) to sleep the smallest one of them to die and exit the simulation
		usleep(philo->data->time_to_die * 1000);
	else
		usleep(philo->data->time_to_eat * 1000);

	release_forks(philo);
	return 0;
}