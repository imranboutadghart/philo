/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:34 by iboutadg          #+#    #+#             */
/*   Updated: 2024/08/15 01:36:36 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str, int *err)
{
	size_t	i;
	long	res;

	i = 0;
	res = 0;
	if (!str[i])
		*err = error(ERR_EMPTY_ARG);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if ((res > 2147483647))
			*err = error(ERR_TOO_BIG_ARG);
	}
	if (str[i])
		*err = error(ERR_INVALID_INPUT);
	return (res);
}

void	parse(t_data *data, int ac, char **av)
{
	data->err = 0;
	data->end = 0;
	if (!(5 == ac || 6 == ac))
	{
		data->err = error(ERR_WRONG_NUM_ARG);
		return ;
	}
	data->philo_num = ft_atoi(av[1], &data->err);
	if (data->err)
		return ;
	data->ttd = ft_atoi(av[2], &data->err);
	if (data->err)
		return ;
	data->tte = ft_atoi(av[3], &data->err);
	if (data->err)
		return ;
	data->tts = ft_atoi(av[4], &data->err);
	if (6 == ac)
		data->min_eats = ft_atoi(av[5], &data->err);
	else
		data->min_eats = -1;
	return ;
}
