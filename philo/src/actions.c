#include "philo.h"

static void take_forks(int i, t_data *data)
{
	pthread_mutex_lock(data->philos[i % data->args.philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
	pthread_mutex_lock(data->philos[i + 1 % data->args.philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
}

static void take_forks_reversed(int i, t_data *data)
{
	pthread_mutex_lock(data->philos[i + 1 % data->args.philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
	pthread_mutex_lock(data->philos[i % data->args.philo_num].m_fork);
	print_action(data, YEL"%ld has taken a fork"WHT"\n", i);
}

void	put_forks(int i, t_data *data)
{
	pthread_mutex_unlock(data->philos[i].m_fork);
	pthread_mutex_unlock(data->philos[(i + 1) %	 data->args.philo_num].m_fork);
}

void	eating(int i, t_data *data)
{
	t_timeval	tv;

	if (i % 2)
		take_forks(i, data);
	else
		take_forks_reversed(i, data);
	pthread_mutex_lock(data->philos[i].m_philo);
	tv = get_timeval(data);
	print_action(data, MAG"%ld is eating"WHT"\n", i);
	data->philos[i].last_meal = tv;
	pthread_mutex_unlock(data->philos[i].m_philo);
	usleep(data->args.tte * 1000);
	put_forks(i, data);
}
void	sleeping(int i, t_data *data)
{
	print_action(data, GRN"%ld is sleeping"WHT"\n", i);
	usleep(data->args.tts * 1000);
}
void	thinking(int i, t_data *data)
{
	print_action(data, BLU"%ld is thinking"WHT"\n", i);
}

