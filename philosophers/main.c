#include "philosophers.h"



static void join_all(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nb)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}


int main(int ac, char **av)
{
	t_data *data;

	if(ft_isnot_valid_args(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if(init_data(data, ac,av))
		return (free(data),1);
	if (init_mutexes(data))
		return(free(data),1);
	if(init_philos(data))
		return(cleanup(data),1);
	if(thread_creation(data))
		cleanup(data);
	join_all(data);
	cleanup(data);
	return (EXIT_SUCCESS);
}
