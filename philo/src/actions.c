#include "philo.h"

void	eating(long i)
{
	t_args	args;
	struct timeval	tv;

	args = get_args(1, 0);
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(get_fork(i));
	pthread_mutex_lock(get_fork(i + 1));
	printf(RED"%ld %ld is eating"WHT"\n", tv.tv_usec, i + 1);
	usleep(args.tte);
	pthread_mutex_unlock(get_fork(i));
	pthread_mutex_unlock(get_fork(i + 1));
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
	usleep(args.ttd);
}

// timestamp_in_ms X has taken a fork
// timestamp_in_ms X died

