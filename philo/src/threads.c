/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:46 by iboutadg          #+#    #+#             */
/*   Updated: 2024/10/01 06:20:22 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_data *data, int i)
{
	t_timeval	tv;

	tv = get_timeval(data);
	if (time_difference(tv, data->philos[i].last_meal) > data->ttd)
	{
		pthread_mutex_lock(&data->m_err);
		print_time(tv);
		printf(RED"%d died"WHT"\n", i + 1);
		data->end = 1;
		pthread_mutex_unlock(&data->m_err);
		pthread_mutex_unlock(&data->philos[i].m_philo);
		return (1);
	}
	return (0);
}

void	*monitoring(void *dt)
{
	int			looping;
	int			i;
	t_data		*data;

	data = (t_data *)dt;
	looping = 1;
	while (looping)
	{
		usleep(10);
		looping = (data->min_eats == -1);
		i = -1;
		while (++i < data->philo_num)
		{
			pthread_mutex_lock(&data->philos[i].m_philo);
			if (philo_died(data, i))
				return (NULL);
			if (!looping && data->philos[i].meals < data->min_eats)
				looping = 1;
			pthread_mutex_unlock(&data->philos[i].m_philo);
		}
	}
	pthread_mutex_lock(&data->m_err);
	data->end = 1;
	pthread_mutex_unlock(&data->m_err);
	return (NULL);
}

void	*routine(void *thread_args)
{
	int		i;
	t_data	*data;

	i = ((t_thread_arg *)thread_args)->i;
	data = ((t_thread_arg *)thread_args)->data;
	if (data->philo_num % 2 && i == data->philo_num - 1)
		my_usleep(data->tte * 1500, data);
	if (i % 2)
		my_usleep(data->tte * 500, data);
	while (1)
	{
		eating(i, data);
		sleeping(i, data);
		thinking(i, data);
		if (data->philo_num % 2)
			my_usleep(max(data->tte * 2 - data->tts, 0) * \
				(500 * (i % 2) + 200 * (i == data->philo_num - 1)), data);
		pthread_mutex_lock(&data->m_err);
		if (data->err || data->end)
			return (pthread_mutex_unlock(&data->m_err), NULL);
		pthread_mutex_unlock(&data->m_err);
	}
	return (NULL);
}
