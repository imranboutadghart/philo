/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:40 by iboutadg          #+#    #+#             */
/*   Updated: 2024/08/15 01:36:43 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_threads(t_data *data, pthread_t **threads, t_thread_arg **th_args)
{
	*threads = malloc(data->philo_num * sizeof(pthread_t));
	if (!*threads)
		return (data->err = error(ERR_MALLOC_THREADS), data->err);
	*th_args = create_thread_args(data);
	if (data->err)
		return (free(threads), data->err);
	return (0);
}

int	create_threads(t_data *data, pthread_t *threads, t_thread_arg *th_args)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(threads + i, NULL, routine, (void *)(th_args + i)))
		{
			pthread_mutex_lock(&data->m_err);
			data->err = error(ERR_CREAT_THREAD);
			pthread_mutex_unlock(&data->m_err);
			return (i);
		}
		i++;
	}
	return (0);
}

int	start_simulation(t_data *data)
{
	pthread_t		*threads;
	pthread_t		monitor_thread;
	t_thread_arg	*th_args;
	int				i;

	if (alloc_threads(data, &threads, &th_args))
		return (data->err);
	i = create_threads(data, threads, th_args);
	pthread_mutex_lock(&data->m_err);
	if (!data->err)
	{
		pthread_mutex_unlock(&data->m_err);
		pthread_create(&monitor_thread, NULL, monitoring, (void *)data);
		pthread_join(monitor_thread, NULL);
		i = data->philo_num - 1;
	}
	else
		pthread_mutex_unlock(&data->m_err);
	while (i >= 0)
		if (pthread_join(threads[i--], NULL))
			data->err = error(ERR_JOIN_THREAD);
	free(th_args);
	free(threads);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av);
	if (data.err)
		return (1);
	if (data.philo_num == 1)
	{
		pthread_mutex_lock(&data.philos[0].m_fork);
		print_action(&data, YEL"%ld has taken a fork"WHT"\n", 0);
		usleep(data.ttd * 1000);
		print_time(get_timeval(&data));
		printf(RED"%d died"WHT"\n", 1);
		pthread_mutex_unlock(&data.philos[0].m_fork);
		destroy_data(&data);
		return (data.err);
	}
	start_simulation(&data);
	destroy_data(&data);
	return (data.err);
}
