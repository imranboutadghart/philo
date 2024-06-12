#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

typedef struct s_args
{
	int	philo_num;
	int	ttd;
	int	tte;
	int	tts;
	int	min_eats;
}	t_args;

typedef struct s_philo
{
	pthread_mutex_t	m_fork;
	pthread_mutex_t	m_philo;
	suseconds_t		last_meal;
	int				meals;
} t_philo;


t_args			get_args(void);
void			parse(int ac, char **av);
int				error(void);

//actions
void			eating(long i);
void			sleeping(long i);
void			thinking(long i);

suseconds_t get_u_timeofday();

suseconds_t	get_last_meal(long i);
void			set_last_meal(long i, struct timeval tv);
void			kill_philos(void);
t_philo			*get_philos();


#endif
