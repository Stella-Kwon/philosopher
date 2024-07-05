/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:46:02 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/05 19:31:08 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int unlock_mutex(pthread_mutex_t *mutex, char *name_of_mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("%s : thread_mutex_unlock has been failed\n", name_of_mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int lock_mutex(pthread_mutex_t *mutex, char *name_of_mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("%s : thread_mutex_lock has been failed\n", name_of_mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int init_mutex(pthread_mutex_t *mutex, char *name_of_mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("%s : thread_mutex_init has been failed\n", name_of_mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int destroy_mutex(pthread_mutex_t *mutex, char *name_of_mutex)
{
	(void)name_of_mutex;
	if (pthread_mutex_destroy(mutex) != 0)
	{
		perror ("reason : ");
		printf("%s : thread_mutex_destroy has been failed\n", name_of_mutex);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int rm_all_mutex(t_data *data)
{
	size_t	i;

	i=0;
	while (i < data->num_philos)
	{
		printf("id : %ld\n", i);
		if (destroy_mutex(&data->forks[i], "&data->forks[i]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (destroy_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (destroy_mutex(&data->error_lock, "data->error_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (destroy_mutex(&data->print_lock, "data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (destroy_mutex(&data->lastmeal_lock, "data->lastmeal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
