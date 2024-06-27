/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:17:23 by sukwon            #+#    #+#             */
/*   Updated: 2024/06/26 22:18:07 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data *data, int actions)
{
	pthread_mutex_lock(&(data->print_lock));
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
	pthread_mutex_unlock(&(data->print_lock));
}
