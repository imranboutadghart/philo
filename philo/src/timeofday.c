#include "philo.h"

suseconds_t get_u_timeofday()
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_usec);
}