/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:21:49 by iboutadg          #+#    #+#             */
/*   Updated: 2024/05/14 13:01:06 by iboutadg         ###   ########.fr       */
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
	if (!(data->end || data->err) && PRINT)
	{
		print_time(tv);
		printf(str, i + 1);
	}	
}
