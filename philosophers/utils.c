#include "philosophers.h"

long long	gtime_ms(void)
{
	struct timeval	tv;
    long long time_now;

    time_now = 0;
	if (gettimeofday(&tv, NULL) == -1)
    {
        write(2,"gettimeofday Error \n",20);
    }
    time_now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000); 
	return (time_now);
}
