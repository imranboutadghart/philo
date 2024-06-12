#include "philo.h"

t_philo *get_philos()
{
	static t_philo	*philos;
	static t_args	args;
	int				j;

	if (!philos)
	{
		args = get_args();
		philos = malloc(args.philo_num * sizeof(t_philo));
		j = 0;
		while (j < args.philo_num)
        {
			pthread_mutex_init(&(philos[j].m_fork), NULL);
			pthread_mutex_init(&(philos[j].m_philo), NULL);
            j++;
        }
	}
	return (philos);
}

void	kill_philos(void)
{
	t_args	args;
	t_philo	*philos;
	int 	i;

	i = 0;
	args = get_args();
	philos = get_philos();
	while (i < args.philo_num)
    {
		pthread_mutex_destroy(&philos[i].m_fork);
		pthread_mutex_destroy(&philos[i].m_philo);
    }
	free(philos);
}

void set_last_meal(long i, suseconds_t time)
{
    t_philo *philos;

    philos = get_philos();
    philos[i].last_meal = time;
}

suseconds_t get_last_meal(long i)
{
    t_philo *philos;

    philos = get_philos();
    return (philos[i].last_meal);
}
