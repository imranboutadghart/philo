#include "philo.h"

static void take_fork(long i)
{
	t_args			args;
	t_philo			*philos;

	philos = get_philos();
	args = get_args();
	pthread_mutex_lock(&philos[i % args.philo_num].m_fork);
	printf(YEL"%ld %ld has taken a fork"WHT"\n", get_u_timeofday, i + 1);
}

void	put_fork(long i)
{
	t_args	args;
	t_philo	*philos;

	philos = get_philos();
	args = get_args();
	pthread_mutex_unlock(&philos[i % args.philo_num].m_fork);
}

void	eating(long i)
{
	t_args		args;
	suseconds_t	time;
	t_philo		*philos;

	args = get_args();
	philos = get_philos();
	take_fork(i);
	take_fork(i + 1);
	time = get_u_timeofday;
	printf(MAG"%ld %ld is eating"WHT"\n", time, i + 1);
	pthread_mutex_lock(&philos[i].m_philo);
	set_last_meal(i, time);
	pthread_mutex_unlock(&philos[i].m_philo);
	usleep(args.tte);
	put_fork(i);
	put_fork(i + 1);
}
void	sleeping(long i)
{
	t_args	args;
	struct timeval	tv;

	args = get_args();
	gettimeofday(&tv, NULL);
	printf(GRN"%ld %ld is sleeping"WHT"\n", tv.tv_usec, i + 1);
	usleep(args.tts);
}
void	thinking(long i)
{
	t_args	args;
	struct timeval	tv;

	args = get_args();
	gettimeofday(&tv, NULL);
	printf(BLU"%ld %ld is thinking"WHT"\n", tv.tv_usec, i + 1);
}

