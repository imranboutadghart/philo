/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:37:15 by iboutadg          #+#    #+#             */
/*   Updated: 2024/09/21 21:44:13 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define PRINT 1

# define ERR_EMPTY_ARG        "error empty_arg"
# define ERR_TOO_BIG_ARG      "error too_big_arg"
# define ERR_INVALID_INPUT    "error invalid_input"
# define ERR_WRONG_NUM_ARG    "error wrong_num_arg"
# define ERR_MALLOC_THREADS   "error malloc_threads"
# define ERR_MALLOC_PHILOS    "error malloc_philos"
# define ERR_MALLOC_THRD_ARGS "error malloc_thrd_args"
# define ERR_CREAT_THREAD     "error creat_thread"
# define ERR_JOIN_THREAD      "error join_thread"
# define ERR_GET_TIME         "error get_time"

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	pthread_mutex_t	m_fork;
	pthread_mutex_t	m_philo;
	t_timeval		last_meal;
	int				meals;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	m_err;
	int				err;
	int				end;
	int				philo_num;
	int				ttd;
	int				tte;
	int				tts;
	int				min_eats;
}	t_data;

typedef struct s_thread_arg
{
	int		i;
	t_data	*data;
}	t_thread_arg;

//parsing
void			parse(t_data *data, int ac, char **av);

//error
int				error(char *str);

//time
t_timeval		get_timeval(t_data *data);
long			time_difference(t_timeval tv1, t_timeval tv2);
t_timeval		print_time(t_timeval tv);
int				my_usleep(int time, t_data *data);

//data
void			init_data(t_data *data, int ac, char **av);
void			destroy_data(t_data *data);
t_thread_arg	*create_thread_args(t_data	*data);

//actions
void			eating(int i, t_data *data);
void			sleeping(int i, t_data *data);
void			thinking(int i, t_data *data);
void			print_action(t_data *data, char *str, int i);

//threads
void			*routine(void *thread_args);
void			*monitoring(void *dt);

//utils
int				max(int a, int b);

#endif
