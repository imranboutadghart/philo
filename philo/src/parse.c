#include "philo.h"

static int	ft_atoi(const char *str, int *err)
{
	size_t	i;
	long	res;

	i = 0;
	res = 0;
	if (!str[i])
		*err = error(ERR_EMPTY_ARG, NULL);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if ((res > 2147483647))
			*err = error(ERR_TOO_BIG_ARG, NULL);
	}
	if (str[i])
		*err = error(ERR_INVALID_INPUT, NULL);
	return (res);
}

t_args	parse(int ac, char **av)
{
	t_args	args;

	args.err = 0;
	if (!(5 == ac || 6 == ac))
	{
		args.err = error(ERR_WRONG_NUM_ARG, NULL);
		return (args);
	}
	args.philo_num = ft_atoi(av[1], &args.err);
	if (args.err)
		return (args);
	args.ttd = ft_atoi(av[2], &args.err);
	if (args.err)
		return (args);
	args.tte = ft_atoi(av[3], &args.err);
	if (args.err)
		return (args);
	args.tts = ft_atoi(av[4], &args.err);
	if (6 == ac)
		args.min_eats = ft_atoi(av[5], &args.err);
	else
		args.min_eats = -1;
	if (args.err)
		return (args);
	return (args);
}
