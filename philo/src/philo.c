#include "philo.h"

void	*monitoring(void *dt)
{
	int			looping;
	int			i;
	t_timeval	tv;
	t_data		*data;

	data = (t_data *)dt;
	looping = 1;
	while (looping)
	{
		i = -1;
		looping = 0;
		while (++i < data->args.philo_num)
		{
			pthread_mutex_lock(data->philos[i].m_philo);
			tv = get_timeval(data);
			if (data->err)
				return (pthread_mutex_unlock(data->philos[i].m_philo), NULL);
			if (time_difference(tv, data->philos[i].last_meal) > data->args.ttd)
			{
				pthread_mutex_lock(data->m_print);
				print_time(tv);
				printf(MAG"%d died"WHT"\n", i + 1);
				printf(RED"diff = %ld\n", time_difference(tv, data->philos[i].last_meal));
				data->end = 1;
				pthread_mutex_unlock(data->philos[i].m_philo);
				return (NULL);
			}
			if (data->philos[i].meals < data->args.min_eats)
				looping = 1;
			pthread_mutex_unlock(data->philos[i].m_philo);
		}
	}
	data->end = 1;
	return (NULL);
}

void	*routine(void *thread_args)
{
	int		i;
	t_data	*data;

	i = ((t_thread_arg *)thread_args)->i;
	data = ((t_thread_arg *)thread_args)->data;
	if (i % 2)
		usleep(data->args.tte * 1000);
	while (1)
	{
		eating(i, data);
		sleeping(i, data);
		thinking(i, data);
		if (data->err || data->end)
			return (NULL);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	pthread_t		*philosophers;
	pthread_t		monitor;
	t_thread_arg	*th_args;
	int				i;

	philosophers = malloc(data->args.philo_num * sizeof(pthread_t));
	if (!philosophers)
	{
		data->err= error(ERR_MALLOC_THREADS, NULL);
		return ;
	}
	th_args = create_thread_args(data);
	if (data->err)
	{
		free(philosophers);
		return ;
	}
	i = 0;
	while (i < data->args.philo_num)
	{
		if (pthread_create(philosophers + i, NULL, routine, (void*)(th_args + i)))
			{
				data->err = error(ERR_CREAT_THREAD, data);
				break ;
			}
		i++;
	}
	if (!data->err)
	{
		pthread_create(&monitor, NULL, monitoring, (void *)data);
		pthread_join(monitor, NULL);
		i = data->args.philo_num - 1;
		// if (data->err || data->end)
		// {
		// 	detach_philos(data, philosophers);
		// 	unlock_if_locked(data->m_print);
		// 	i = -1;
		// }
	}
	while (i >= 0)
	{
		if (pthread_join(philosophers[i], NULL))
			data->err = error(ERR_JOIN_THREAD, data);
		i--;
	}
	free(th_args);
	free(philosophers);
}

int main(int ac, char **av)
{
	t_args	args;
	t_data	data;

	args.err = 0;
	args = parse(ac, av);
	if (args.err)
		return (1);
	data.err = 0;
	data = init_data(args);
	if (data.err)
		return (1);
	start_simulation(&data);
	destroy_data(&data);
	return (data.err);
}
