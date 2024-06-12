#include "philo.h"

void	*monitoring(void *data)
{
	t_args			args;
	t_philo			*philos;
	struct timeval	tv;
	int				looping;
	int				i;

	(void) data;
	looping = 1;
	args = get_args(1, 0);
	philos = get_philos();
	while (looping)
	{
		i = 0;
		while (i < args.philo_num)
		{
			pthread_mutex_lock(&philos[i].m_philo);
			get_last_meal(i);
		}
	}
}

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
	pthread_t	*philosophers;
	pthread_t	monitor;
	int			i;

	args = get_args(1, 0);
	philosophers = malloc(args.philo_num * sizeof(pthread_t));
	i = 0;
	while (i < args.philo_num)
	{
		if (pthread_create(philosophers + i, NULL, do_actions, (void*)(long)i))
			/*handle error*/;
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, NULL);
	i = 0;
	while (i < args.philo_num)
	{
		if (pthread_join(philosophers[i], NULL))
			/*handle error*/;
		i++;
	}
	free(philosophers);
}

int main(int ac, char **av)
{
	parse(ac, av);
	start_simulation();
}
