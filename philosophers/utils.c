#include "philosophers.h"

long long	get_current_time_ms(void)
{
	struct timeval	tv;
    long long time_now;

    time_now = 0;
	if (gettimeofday(&tv, NULL) == -1)
    {
        write(2,"gettimeofday Error \n",20);
        return(0);
    }
    time_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); 
	return (time_now);
}

int did_someone_die(t_data *data)
{
    int ret;

    ret = 0;
    pthread_mutex_lock(&data->someone_mutex);
    ret = data->someone_died;
    pthread_mutex_unlock(&data->someone_mutex);
    return (ret);
}