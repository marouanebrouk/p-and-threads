
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
		if (!ft_is_digit(av[i]) || ft_atoi(av[i]) <= 0)
		{
			write(2, "Error: invalid argument value\n", 30);
			return (1);
		}
		i++;
	}
	return (0);
}
