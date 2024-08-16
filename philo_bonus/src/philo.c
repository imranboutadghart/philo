#include "philo.h"

static int start_simulation(t_data *data)
{
	int	i;
	int	pid;

	i = 0;
	while (i < data->philo_num)
	{
		pid = fork();
		if (!pid)
			do_actions(data, i);
		else
			data->philos[i].pid = pid;
	}
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	if (data.err)
		return (1);
	if (data.philo_num == 1)
	{
		print_action(&data, YEL"%ld has taken a fork"WHT"\n", 0);
		usleep(data.ttd * 1000);
		print_time(get_timeval(&data));
		printf(RED"%d died"WHT"\n", 1);
		destroy_data(&data);
		return (data.err);
	}
	data.err = start_simulation(&data);
	if (data.err)
		return (data.err);
	destroy_data(&data);
	return (data.err);
}
