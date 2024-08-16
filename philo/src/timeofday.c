/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timeofday.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:51 by iboutadg          #+#    #+#             */
/*   Updated: 2024/08/15 01:36:55 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timeval	get_timeval(t_data *data)
{
	t_timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		pthread_mutex_lock(&data->m_err);
		data->err = error(ERR_GET_TIME);
		pthread_mutex_unlock(&data->m_err);
	}
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
