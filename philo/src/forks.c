#include "philo.h"

pthread_mutex_t	*get_fork(long i)
{
	static pthread_mutex_t	*forks;
	static t_args			args;
	int						j;

	if (!forks)
	{
		args = get_args(1, NULL);
		forks = malloc(args.philo_num * sizeof(pthread_mutex_t));
		j = 0;
		while (j < args.philo_num)
			pthread_mutex_init(forks + j++, NULL);
	}
	return (forks + (i % args.philo_num));
}

void	kill_forks(void)
{
	t_args			args;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	args = get_args(1, NULL);
	forks = get_fork(0);
	while (i < args.philo_num)
		pthread_mutex_destroy(forks + i++);
	free(forks);
}