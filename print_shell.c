/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:17:23 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/05 17:47:03 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_action(t_data *data, int actions, int philo)
{
	size_t time;
	// unlock할떼 다른 이전 lock해준것을 커버해줘야해서
	// 따로 actions.c에다가 빼줌 print 부르기 이전에
	// if (lock_mutex(&(data->print_lock), "data->print_lock") == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	time = get_time(data);
	if (time == (size_t)-100)
		return (EXIT_FAILURE);
	time = time - data->init_time;
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
	// if (unlock_mutex(&(data->print_lock), "data->print_lock") == EXIT_FAILURE)
	// {
	// 	if ()

	// 	 return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}

int	error_print(char *msg)
{
	printf("%s\n", msg);
	return (EXIT_FAILURE); // 1
}