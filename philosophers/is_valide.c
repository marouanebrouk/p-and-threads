
#include "philosophers.h"

static int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int ft_atoi(char *str)
{
    int sign;
    int result;

    sign = 1;
    result = 0;
    while ((*str >= 9 && *str <= 13 ) || *str == 32)
        str++;
    if (*str == '-' || *str == '+' )
        if (*(str++) == '-')
            sign = -1;
    while (*str >= '0' && *str <= '9')
        result = result * 10 + (*str++ - '0');
	// if (result * sign < 0)
	// 	return (-1);
    return(result * sign);
}

int	ft_isnot_valid_args(int ac, char **av)
{
	int	i;

    i = 1;
	if (ac != 5 && ac != 6)
	{
		write(2, "Error: wrong number of arguments\n", 33);
		return (1);
	}
	while (i < ac)
	{
		if(!ft_is_digit(av[i]))
			return (write(2, "Error: invalid argument value\n", 30));
		if (i == 1 && ft_atoi(av[1]) > 200)
			return(write(2, "Error : Num of max philo is 200\n", 32));
		if (ft_atoi(av[i]) < 0)
			return (write(2, "Error: invalid argument value\n", 30));
		i++;
	}
	return (0);
}
