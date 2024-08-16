#include "philo.h"

static void	*monitoring(void *dt)
{
	int			looping;
	int			i;
	t_timeval	tv;
	t_data		*data;

	data = (t_data *)dt;
	looping = 1;
	while (looping)
	{
		looping = (data->min_eats == -1);
		i = -1;
		while (++i < data->philo_num)
		{
			pthread_mutex_lock(&data->philos[i].m_philo);
			tv = get_timeval(data);
			if (time_difference(tv, data->philos[i].last_meal) > data->ttd)
			{
				pthread_mutex_lock(&data->m_err);
				print_time(tv);
				printf(RED"%d died"WHT"\n", i + 1);
				data->end = 1;
				pthread_mutex_unlock(&data->m_err);
				pthread_mutex_unlock(&data->philos[i].m_philo);
				return (NULL);
			}
			if (!looping && data->philos[i].meals < data->min_eats)
				looping = 1;
			pthread_mutex_unlock(&data->philos[i].m_philo);
		}
	}
	data->end = 1;
	return (NULL);
}

static void	*routine(void *thread_args)
{
	int		i;
	t_data	*data;

	i = ((t_thread_arg *)thread_args)->i;
	data = ((t_thread_arg *)thread_args)->data;
	if (i % 2)
		usleep(data->tte * 500);
	while (1)
	{
		eating(i, data);
		sleeping(i, data);
		thinking(i, data);
		pthread_mutex_lock(&data->m_err);
		if (data->err || data->end)
			return (pthread_mutex_unlock(&data->m_err), NULL);
		pthread_mutex_unlock(&data->m_err);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	pthread_t		*threads;
	pthread_t		monitor_thread;
	t_thread_arg	*th_args;
	int				i;

	threads = malloc(data->philo_num * sizeof(pthread_t));
	if (!threads)
	{
		data->err= error(ERR_MALLOC_THREADS);
		return ;
	}
	th_args = create_thread_args(data);
	if (data->err)
	{
		free(threads);
		return ;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(threads + i, NULL, routine, (void*)(th_args + i)))
		{
			pthread_mutex_lock(&data->m_err);
			data->err = error(ERR_CREAT_THREAD);
			pthread_mutex_unlock(&data->m_err);
			break ;
		}
		i++;
	}
	pthread_mutex_lock(&data->m_err);
	if (!data->err)
	{
		pthread_mutex_unlock(&data->m_err);
		pthread_create(&monitor_thread, NULL, monitoring, (void *)data);
		pthread_join(monitor_thread, NULL);
		i = data->philo_num - 1;
		//if (data->err || data->end)
		//{
		//	detach_philos(data, threads);
		//	unlock_if_locked(data->m_print);
		//	i = -1;
		//}
	}
	else
		pthread_mutex_unlock(&data->m_err);
	while (i >= 0)
	{
		if (pthread_join(threads[i], NULL))
			data->err = error(ERR_JOIN_THREAD);
		i--;
	}
	free(th_args);
	free(threads);
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
	start_simulation(&data);
	destroy_data(&data);
	return (data.err);
}
