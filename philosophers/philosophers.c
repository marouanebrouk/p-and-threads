#include "philosophers.h"

int main(int ac, char **av)
{
    if (ac == 5 || ac == 6)
    {
        ft_atoi(av[1]);
        ft_atoi(av[2]);
        ft_atoi(av[3]);
        ft_atoi(av[4]);
        if(ac == 6)
            ft_atoi(av[5]);
    }
    else
    {
        write(1,"Arguments not correct !\n",24);
        exit(1);
    }
}