#include "philo.h"

t_timeval	get_timeval(t_data *data)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
		data->err = error(ERR_GET_TIME, data);
	return (tv);
}

long	time_difference(t_timeval tv1, t_timeval tv2)
{
	return (((tv1.tv_sec - tv2.tv_sec) * 1000 + \
			tv1.tv_usec / 1000 - tv2.tv_usec / 1000));
}

t_timeval	print_time(t_timeval tv)
{
	printf("%ld.%03ld ", tv.tv_sec, tv.tv_usec / 1000);
	return (tv);
}
