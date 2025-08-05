#include "philosophers.h"


int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = -1;
	if (!ft_is_valid_args(ac, av))
		return (1);
	if (!ft_init_data(&data, ac, av))
		return (1);
	if (!ft_init_philosophers(&data))
		return (1);
	while (++i < data.philo_nb)
	{
		if (pthread_create(&data.philos[i].thread, NULL, &ft_routine, &data.philos[i]) != 0)
		{
			write(2, "Error: failed to create thread\n", 31);
			return (1);
		}
	}
	i = -1;
	while (++i < data.philo_nb)
		pthread_join(data.philos[i].thread, NULL);
	return (0);
}
