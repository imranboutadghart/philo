/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:41:18 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/20 01:18:24 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(int i, t_data *data)
{
	pthread_mutex_lock(&data->philos[i % data->philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
	pthread_mutex_lock(&data->philos[(i + 1) % data->philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
}

static void	take_forks_reversed(int i, t_data *data)
{
	pthread_mutex_lock(&data->philos[(i + 1) % data->philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
	pthread_mutex_lock(&data->philos[i % data->philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
}

void	eating(int i, t_data *data)
{
	t_timeval	tv;

	if (i % 2)
		take_forks(i, data);
	else
		take_forks_reversed(i, data);
	pthread_mutex_lock(&data->philos[i].m_philo);
	tv = get_timeval(data);
	print_action(data, MAG"%ld is eating"WHT"\n", i);
	data->philos[i].last_meal = tv;
	data->philos[i].meals++;
	pthread_mutex_unlock(&data->philos[i].m_philo);
	my_usleep(data->tte * 1000, data);
	pthread_mutex_unlock(&data->philos[i].m_fork);
	pthread_mutex_unlock(&data->philos[(i + 1) % data->philo_num].m_fork);
}

void	sleeping(int i, t_data *data)

{
	print_action(data, GRN"%ld is sleeping"WHT"\n", i);
	my_usleep(data->tts * 1000, data);
}

void	thinking(int i, t_data *data)
{
	print_action(data, BLU"%ld is thinking"WHT"\n", i);
}
