#include "philo.h"

void	*do_actions(void *i)
{
	eating((long)i);
	sleeping((long)i);
	thinking((long)i);
	return (NULL);
}

void	start_simulation()
{
	t_args		args;
	pthread_t	*threads;
	int			i;

	args = get_args(1, 0);
	threads = malloc(args.philo_num * sizeof(pthread_t));
	i = 0;
	while (i < args.philo_num)
	{
		if (pthread_create(threads + i, NULL, do_actions, (void*)(long)i))
			/*handle error*/;
		i++;
	}
	i = 0;
	while (i < args.philo_num)
	{
		if (pthread_join(threads[i], NULL))
			/*handle error*/;
		i++;
	}
	free(threads);
}

int main(int ac, char **av)
{
	parse(ac, av);
	start_simulation();
}
