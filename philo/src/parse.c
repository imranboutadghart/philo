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

void	parse(int ac, char **av)
{
	t_args	args;

	if (!(5 == ac || 6 == ac))
		exit(error());
	args.philo_num = ft_atoi(av[1]);
	args.ttd = ft_atoi(av[2]);
	args.tte = ft_atoi(av[3]);
	args.tts = ft_atoi(av[4]);
	if (6 == ac)
		args.min_eats = ft_atoi(av[5]);
	else
		args.min_eats = -1;
	set_args(0, &args);
}

static t_args	set_args(int get, t_args *args)
{
	static t_args g_args;

	if (get)
		return (g_args);
	g_args = *args;
	return (g_args);
}

t_args	get_args()
{
	return (set_args(1, NULL));
}