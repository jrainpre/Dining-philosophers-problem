#include "philosophers.h"

int get_input(int argc, char **argv, t_global *global)
{
    int temp;

    if (argc < 4 || argc > 6)
        return(0);
    if (argc >= 5)
        {
            global->nbr_ps = ft_atoi(argv[1]);
            temp = ft_atoi(argv[2]);
            global->ttd = temp;
            temp = ft_atoi(argv[3]);
            global->tte = temp;
            temp = ft_atoi(argv[4]);
            global->tts = temp;
            global->must_eat = -1;
        }
    if (argc == 6)
        global->must_eat = ft_atoi(argv[5]);
    return(1);
}


unsigned long get_time(void)
{
    struct timeval time;
    unsigned long time_msec;

    gettimeofday(&time, NULL);
    time_msec = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    return (time_msec);
}

void wait(unsigned long time_msec)
{
    usleep(1000 * time_msec);
}