#include "philo.h"

void	start_simulation(t_params p)
{
	(void)p;
}

int main(int ac, char **av)
{
	t_params	params;

	params = parse(ac, av);
	start_simulation(params);
	printf("%d:%d:%d:%d:%d", params.philo_num, params.ttd, params.tte, params.tts, params.min_eats);
}
