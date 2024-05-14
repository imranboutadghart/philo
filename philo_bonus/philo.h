#ifndef PHILO_h
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <threads.h>

typedef struct s_params
{
	int	philo_num;
	int	ttd;
	int	tte;
	int	tts;
	int	min_eats;
}	t_params;

t_params	parse(int ac, char **av);
int			error(void);

#endif
