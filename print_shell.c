/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:17:23 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 22:38:03 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int actions, int philo)
{
	size_t	time;

	time = get_time();
	if (time == (size_t)-100)
		return (EXIT_FAILURE);
	time = time - data->init_time;
	if (check_all_alive(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lock_mutex(&(data->print_lock), "data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	printf("%ld %d ", time, philo);
	if (actions == DIED)
		printf("died\n");
	else if (actions == TAKEN_FORKS)
		printf("has taken a fork\n");
	else if (actions == EATING)
		printf("is eating\n");
	else if (actions == THINKING)
		printf("is thinking\n");
	else if (actions == SLEEPING)
		printf("is sleeping\n");
	if (unlock_mutex(&(data->print_lock), \
	"data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	error_print(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}
