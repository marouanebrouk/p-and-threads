#include "philosophers.h"


int	main(int ac, char **av)
{
	t_rules	rules;
	int		i;
	if (!ft_is_valid_args(ac, av))
		return (1);
	if (!ft_init_rules(&rules, ac, av))
		return (1);
	if (!ft_init_philosophers(&rules))
		return (1);
	i = -1;
	while (++i < rules.nb_philo)
	{
		if (pthread_create(&rules.philos[i].thread, NULL, &ft_routine, &rules.philos[i]) != 0)
		{
			write(2, "Error: failed to create thread\n", 31);
			return (1);
		}
	}
	i = 0;
	while (i < rules.nb_philo)
	{
		pthread_join(rules.philos[i].thread, NULL);
		i++;
	}
	return (0);
}
