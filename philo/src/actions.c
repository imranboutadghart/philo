#include "philo.h"

void	eating(long i)
{
	t_args			args;
	struct timeval	tv;
	t_philo			*philos;

	args = get_args(1, 0);
	philos = get_philos();
	pthread_mutex_lock(&philos[i].m_fork);
	printf(YEL"%ld %ld has taken a fork"WHT"\n", tv.tv_usec, i + 1);
	pthread_mutex_lock(&philos[(i + 1) % args.philo_num].m_fork);
	printf(YEL"%ld %ld has taken a fork"WHT"\n", tv.tv_usec, i + 1);
	pthread_mutex_lock(&philos[i].m_philo);
	gettimeofday(&tv, NULL);
	printf(MAG"%ld %ld is eating"WHT"\n", tv.tv_usec, i + 1);
	set_last_meal(i, tv);
	usleep(args.tte);
	pthread_mutex_unlock(&philos[i].m_fork);
	pthread_mutex_unlock(&philos[(i + 1) % args.philo_num].m_fork);
	pthread_mutex_unlock(&philos[i].m_philo);
}
void	sleeping(long i)
{
	t_args	args;
	struct timeval	tv;

	args = get_args(1, 0);
	gettimeofday(&tv, NULL);
	printf(GRN"%ld %ld is sleeping"WHT"\n", tv.tv_usec, i + 1);
	usleep(args.tts);
}
void	thinking(long i)
{
	t_args	args;
	struct timeval	tv;

	args = get_args(1, 0);
	gettimeofday(&tv, NULL);
	printf(BLU"%ld %ld is thinking"WHT"\n", tv.tv_usec, i + 1);
}

