/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:17:23 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/02 16:42:13 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int actions)
{	
	if (lock_mutex(&(data->print_lock), "data->print_lock"))
		return (EXIT_FAILURE);
	printf("%d %d ", data->timestamps, data->philos->id);
	if (actions == TAKEN_FORKS)
		printf("has taken a fork\n");
	else if (actions == EATING)
		printf("is eating\n");
	else if (actions == THINKING)
		printf("is thinking\n");
	else if (actions == SLEEPING)
		printf("is sleeping\n");
	else if (actions == DIED)
		printf("died\n");
	if (unlock_mutex(&(data->print_lock), "data->print_lock"))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	error_print(t_data	*data, char *msg)
{
	printf("%d\n", msg);
	return (EXIT_FAILURE); // 1
}