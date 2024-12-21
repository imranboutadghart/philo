/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:40 by iboutadg          #+#    #+#             */
/*   Updated: 2024/12/21 19:08:13 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_threads(t_data *data, pthread_t **threads, t_thread_arg **th_args)
{
	*threads = malloc(data->philo_num * sizeof(pthread_t));
	if (!*threads)
		return (data->err = error(ERR_MALLOC_THREADS), data->err);
	*th_args = create_thread_args(data);
	if (data->err)
		return (free(threads), data->err);
	return (0);
}

int	create_threads(t_data *data, pthread_t *threads, t_thread_arg *th_args)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(threads + i, NULL, routine, (void *)(th_args + i)))
		{
			pthread_mutex_lock(&data->m_err);
			data->err = error(ERR_CREAT_THREAD);
			pthread_mutex_unlock(&data->m_err);
			return (i);
		}
		i++;
	}
	return (0);
}

// Function to start the simulation and handle thread creation and monitoring
int	start_simulation(t_data *data)
{
    pthread_t		*threads; // Array of philosopher threads
    pthread_t		monitor_thread; // Thread for monitoring
    t_thread_arg	*th_args; // Arguments for threads
    int				i;

    // Allocate memory for threads and thread arguments
    if (alloc_threads(data, &threads, &th_args))
        return (data->err);
    
    // Create philosopher threads
    i = create_threads(data, threads, th_args);
    pthread_mutex_lock(&data->m_err);
    if (!data->err)
    {
        pthread_mutex_unlock(&data->m_err);
        // Create and join the monitor thread
        // main thread can be used for monitoring as well
        pthread_create(&monitor_thread, NULL, monitoring, (void *)data);
        pthread_join(monitor_thread, NULL);
        i = data->philo_num - 1;
    }
    else
        pthread_mutex_unlock(&data->m_err);
    
    // Join philosopher threads that were created
    // Starts from the last thread that was created cuz there could be an error
    while (i >= 0)
        if (pthread_join(threads[i--], NULL))
            data->err = error(ERR_JOIN_THREAD);
    
    // Free allocated memory
    free(th_args);
    free(threads);
    return (0);
}

// Main function to initialize data, handle single philosopher case, and start the simulation
int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, ac, av); // Initialize data
	if (data.err)
		return (1);
	if (data.philo_num == 1) // Handle single philosopher case
	{
		pthread_mutex_lock(&data.philos[0].m_fork);
		print_action(&data, YEL"%ld has taken a fork"WHT"\n", 0);
		usleep(data.ttd * 1000);
		print_time(get_timeval(&data));
		printf(RED"%d died"WHT"\n", 1);
		pthread_mutex_unlock(&data.philos[0].m_fork);
		destroy_data(&data); // Clean up data
		return (data.err);
	}
	start_simulation(&data); // Start the simulation
	destroy_data(&data); // Clean up data
	return (data.err);
}
