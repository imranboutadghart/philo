/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:21:49 by iboutadg          #+#    #+#             */
/*   Updated: 2024/08/15 01:37:02 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	if (str)
	{
		printf("%s\n", str);
		return (1);
	}
	write(2, "Error\n", 6);
	return (1);
}

void	print_action(t_data *data, char *str, int i)
{
	t_timeval	tv;

	tv = get_timeval(data);
	if (data->err)
		return ;
	pthread_mutex_lock(&data->m_err);
	if (!(data->end || data->err) && PRINT)
	{
		print_time(tv);
		printf(str, i + 1);
	}
	pthread_mutex_unlock(&data->m_err);
}

int	max(int a, int b)
{
	return (a * (a > b) + b * (a <= b));
}
