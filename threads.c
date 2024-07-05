/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:05:41 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/05 16:36:45 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int detach_thread_philos(t_data *data)
{
	size_t i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_detach(data->philos[i].philo) != 0)
		{
			printf("data->philos[%ld].philo : pthread_detach has been failed\n", i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int create_thread_philos(t_data *data)
{
	size_t i;

	i = 0;

	if (pthread_create(&(data->monitor), NULL, monitoring_death, (void *)data) != 0)
	{
		printf("data->monitor : pthread_create has been failed\n");
		return (EXIT_FAILURE);
	}
	while (i < data->num_philos)
	{
		if (pthread_create(&(data->philos[i].philo), NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("data->philos[%ld].philo : pthread_create has been failed\n", i);
			if (detach_thread_philos(data) == 1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int wait_threads(t_data *data)
{
	size_t i;

	i = 0;
	if (pthread_join(data->monitor, NULL) != 0) // NULL can be some varialbes that if the threads has a return value to store
	{
		printf("data->monitor : pthread_join has been failed\n");
		return (EXIT_FAILURE);
	}
	while (i < data->num_philos)
	{
		if (pthread_join(data->philos[i].philo, NULL) != 0) // NULL can be some varialbes that if the threads has a return value to store
		{
			printf("data->philos[%ld].philo : pthread_join has been failed\n", i);
			if (detach_thread_philos(data) == 1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
