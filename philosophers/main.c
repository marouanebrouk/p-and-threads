#include "philosophers.h"

int	main(int ac, char **av)
{
	t_rules	rules;

	if (!is_valid_args(ac, av))
		return (1);
	
	if (!init_rules(&rules, ac, av))
	{
		write(2, "Error: initialization failed\n", 30);
		return (1);
	}

	// next: initialize philosophers + create threads

	return (0);
}
