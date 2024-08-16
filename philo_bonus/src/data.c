#include "philo.h"

void	init_data(t_data *data, int ac, char **av)
{
		t_timeval	tv;
		int			i;

		parse(data, ac, av);
		if (data->err)
			return ;
		data->philos = malloc(data->philo_num * sizeof(t_philo));
		data->err = (!!data->philos);
		return ;
}