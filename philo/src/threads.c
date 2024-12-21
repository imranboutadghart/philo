/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboutadg <iboutadg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 01:36:46 by iboutadg          #+#    #+#             */
/*   Updated: 2024/12/21 20:11:04 by iboutadg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Check if philosopher died
int	philo_died(t_data *data, int i)
{
	t_timeval	tv;

	tv = get_timeval(data);
	if (time_difference(tv, data->philos[i].last_meal) > data->ttd)
	{
		pthread_mutex_lock(&data->m_err);
		print_time(tv);
		printf(RED"%d died"WHT"\n", i + 1);
		data->end = 1;
		pthread_mutex_unlock(&data->m_err);
		pthread_mutex_unlock(&data->philos[i].m_philo);
		return (1);
	}
	return (0);
}

// Function to monitor the state of philosophers
void	*monitoring(void *dt)
{
    int			looping;
    int			i;
    t_data		*data;

    data = (t_data *)dt;
    looping = 1;
    while (looping)
    {
        usleep(10); // Sleep for a short period to reduce CPU usage
        looping = (data->min_eats == -1); // Check if minimum eats is not set
        i = -1;
        while (++i < data->philo_num)
        {
            pthread_mutex_lock(&data->philos[i].m_philo); // Lock philosopher mutex
            if (philo_died(data, i)) // Check if philosopher died
                return (NULL);
            if (!looping && data->philos[i].meals < data->min_eats) // Check if philosopher has eaten less than minimum required
                looping = 1;
            pthread_mutex_unlock(&data->philos[i].m_philo); // Unlock philosopher mutex
        }
    }
    pthread_mutex_lock(&data->m_err); // Lock error mutex
    data->end = 1; // Set end flag
    pthread_mutex_unlock(&data->m_err); // Unlock error mutex
    return (NULL);
}

// Routine function executed by each philosopher thread
void	*routine(void *thread_args)
{
    int		i;
    t_data	*data;

    i = ((t_thread_arg *)thread_args)->i; // Get philosopher index
    data = ((t_thread_arg *)thread_args)->data; // Get shared data

    // Adjust sleep time for odd number of philosophers
    if (data->philo_num % 2 && i == data->philo_num - 1)
        my_usleep(data->tte * 1500, data);
    // This creates a third group if there are an odd number of philosophers
    // This group will only contain the last philosopher
    if (i % 2)
        my_usleep(data->tte * 500, data);

    while (1)
    {
        eating(i, data); // Philosopher eats
        sleeping(i, data); // Philosopher sleeps
        thinking(i, data); // Philosopher thinks

        // Adjust sleep time for odd number of philosophers
        // If number of philosophers is odd, the last philosopher will sleep for a longer time
        // This is to ensure that the last philosopher get a fair chance at eating
        if (data->philo_num % 2)
            my_usleep(max(data->tte * 2 - data->tts, 0) * \
                (500 * (i % 2) + 200 * (i == data->philo_num - 1)), data);

        pthread_mutex_lock(&data->m_err);
        if (data->err || data->end) // Check for errors or end condition
            return (pthread_mutex_unlock(&data->m_err), NULL);
        pthread_mutex_unlock(&data->m_err);
    }
    return (NULL);
}
