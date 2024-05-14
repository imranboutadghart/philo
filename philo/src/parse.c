#include "philo.h"

static int	ft_atoi(const char *str)
{
	size_t	i;
	long	res;

	i = 0;
	res = 0;
	if (!str[i])
		exit(error());
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if ((res > 2147483647))
			exit(error());
	}
	if (str[i])
		exit(error());
	return (res);
}

t_params	parse(int ac, char **av)
{
	t_params	params;

	if (!(5 == ac || 6 == ac))
		exit(error());
	params.philo_num = ft_atoi(av[1]);
	params.ttd = ft_atoi(av[2]);
	params.tte = ft_atoi(av[3]);
	params.tts = ft_atoi(av[4]);
	if (6 == ac)
		params.min_eats = ft_atoi(av[5]);
	else
		params.min_eats = -1;
	return (params);
}

