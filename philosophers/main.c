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
	t_data data;
	if(ft_isnot_valid_args(ac, av))
		return (EXIT_FAILURE);
	if(init_all(&data, ac,av))
		return (EXIT_FAILURE);
	if(thread_creation(&data))
		cleanup(&data);
	join_all(&data);
	printf("all threads JOINED successfully \n");
	cleanup(&data);
	return (EXIT_SUCCESS);
}