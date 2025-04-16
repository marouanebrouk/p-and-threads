#include "philosophers.h"


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


int main(int ac, char **av)
{
    
}