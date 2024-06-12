#include "philo.h"

void	*monitoring(void *data)
{
	t_args	args;
	t_philo	*philos;
	int		looping;
	long	i;
	suseconds_t	time;

	(void) data;
	looping = 1;
	args = get_args();
	philos = get_philos();
	while (looping)
	{
		i = -1;
		while (++i < args.philo_num)
		{
			pthread_mutex_lock(&philos[i].m_philo);
			time = get_u_timeofday();
			if ((time - get_last_meal(i)) < args.ttd)
			{
				printf(MAG"%ld %ld died"WHT"\n", time, i + 1);
				exit(0);
			}
			pthread_mutex_unlock(&philos[i].m_philo);
		}
	}
	return NULL;
}

void	*do_actions(void *i)
{
	t_args	args;

	args = get_args();
	if ((long)i % 2)
		usleep(args.tte / 2);
	while (1)
	{
		eating((long)i);
		sleeping((long)i);
		thinking((long)i);
	}
	return (NULL);
}

void	start_simulation()
{
	t_args		args;
	pthread_t	*philosophers;
	pthread_t	monitor;
	int			i;

	args = get_args();
	philosophers = malloc(args.philo_num * sizeof(pthread_t));
	i = 0;
	while (i < args.philo_num)
	{
		if (pthread_create(philosophers + i, NULL, do_actions, (void*)(long)i))
			/*handle error*/;
		i++;
	}
	pthread_create(&monitor, NULL, monitoring, NULL);
	pthread_join(monitor, NULL);
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
