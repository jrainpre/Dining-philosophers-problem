#include "philosophers.h"

int get_input(int argc, char **argv, t_global *global)
{
    int temp;

    if (argc < 4 || argc > 5)
        return(0);
    if (argc >= 4)
        {
            global->nbr_ps = ft_atoi(argv[1]);
            temp = ft_atoi(argv[2]);
            global->ttd = 1000 * temp;
            temp = ft_atoi(argv[3]);
            global->tte = 1000 * temp;
            global->must_eat = 2147483647;
        }
    if (argc == 5)
        global->must_eat = ft_atoi(argv[4]);
}