/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:05:41 by sukwon            #+#    #+#             */
/*   Updated: 2024/06/28 15:13:35 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int detach_thread_philos(t_data *data)
{
	int i;

	i = 0;
	while (data->philos[i].philo)
	{
		if (pthread_detach(data->philos[i].philo) != 0)
		{
			printf("data->philos[%d].philo : pthread_detach has been failed\n", i);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int create_thread_philos(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&(data->philos[i].philo), NULL, philo_routine, data) != 0)
		{
			printf("data->philos[%d].philo : pthread_create has been failed\n", i);
			if (detach_thread_philos(data) == 1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int wait_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(&data->philos[i].philo, NULL) != 0) // NULL can be some varialbes that if the threads has a return value to store
		{
			printf("data->philos[%d].philo : pthread_join has been failed\n", i);
			if (detach_thread_philos(data) == 1)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
