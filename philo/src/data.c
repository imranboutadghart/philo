/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:29 by iboutadg          #+#    #+#             */
/*   Updated: 2024/08/15 01:36:30 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_philo(t_data *data, int i, t_timeval tv)
{
	data->philos[i].meals = 0;
	data->philos[i].last_meal = tv;
	pthread_mutex_init(&data->philos[i].m_philo, NULL);
	pthread_mutex_init(&data->philos[i].m_fork, NULL);
}

void	init_data(t_data *data, int ac, char **av)
{
	t_timeval	tv;
	int			i;

	parse(data, ac, av);
	if (data->err)
		return ;
	data->philos = malloc(data->philo_num * sizeof(t_philo));
	if (!data->philos)
	{
		data->err = error(ERR_MALLOC_PHILOS);
		return ;
	}
	tv = get_timeval(data);
	if (data->err)
		free(data->philos);
	if (data->err)
		return ;
	i = -1;
	while (++i < data->philo_num)
		init_philo(data, i, tv);
	pthread_mutex_init(&data->m_err, NULL);
	return ;
}

void	destroy_data(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->philos[i].m_fork);
		pthread_mutex_destroy(&data->philos[i].m_philo);
		i++;
	}
	free(data->philos);
}

t_thread_arg	*create_thread_args(t_data	*data)
{
	t_thread_arg	*thread_args;
	int				i;

	thread_args = malloc(data->philo_num * sizeof(t_thread_arg));
	if (!thread_args)
	{
		data->err = error(ERR_MALLOC_THRD_ARGS);
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
