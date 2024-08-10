#include <philo.h>

void	init_philo(t_data *data, int i, t_timeval tv)
{
	data->philos[i].m_fork = malloc(sizeof(pthread_mutex_t));
	data->philos[i].m_philo = malloc(sizeof(pthread_mutex_t));
	data->philos[i].meals = 0;
	data->philos[i].last_meal = tv;
	pthread_mutex_init(data->philos[i].m_philo, NULL);
	pthread_mutex_init(data->philos[i].m_fork, NULL);
}

t_data  init_data(t_args args)
{
	t_data		data;
	t_timeval	tv;
	int			i;

	data.philo_num = args.philo_num;
	data.args = args;
	data.err = 0;
	data.end = 0;
	data.philos = malloc(data.philo_num * sizeof(t_philo));
	if (!data.philos)
	{
		data.err = error(ERR_MALLOC_PHILOS, NULL);
		return (data);
	}
	i = 0;
	tv = get_timeval(&data);
	if (data.err)
	{
		free(data.philos);
		return (data);
	}
	while (i < data.philo_num)
	{
		init_philo(&data, i, tv);
		i++;
	}
	data.m_print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data.m_print, NULL);
	return (data);
}

void  destroy_data(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_num)
	{
		unlock_if_locked(data->philos[i].m_philo);
		unlock_if_locked(data->philos[i].m_fork);
		pthread_mutex_destroy(data->philos[i].m_fork);
		pthread_mutex_destroy(data->philos[i].m_philo);
		free(data->philos[i].m_philo);
		free(data->philos[i].m_fork);
		i++;
	}
	pthread_mutex_destroy(data->m_print);
	free(data->m_print);
	free(data->philos);
}

t_thread_arg	*create_thread_args(t_data	*data)
{
	t_thread_arg	*thread_args;
	int				i;

	thread_args = malloc(data->philo_num * sizeof(t_thread_arg));
	if (!thread_args)
	{
		data->err = error(ERR_MALLOC_THRD_ARGS, NULL);
		return (NULL);
	}
	i = 0;
	while (i < data->philo_num)
	{
		thread_args[i].data = data;
		thread_args[i].i = i;
		i++;
	}
	return (thread_args);
}

void	detach_philos(t_data *data, pthread_t *philosophers)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
		pthread_detach(philosophers[i++]);
}