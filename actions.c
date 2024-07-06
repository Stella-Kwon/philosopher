/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:14:36 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 22:28:10 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	last_meal_time(t_threads *philo)
{
	if (lock_mutex(&(philo->data->lastmeal_lock), \
	"data->lastmeal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->last_meal = get_time();
	if (philo->last_meal == (size_t)-100)
	{
		if (unlock_mutex(&philo->data->lastmeal_lock, \
		"data->lastmeal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (unlock_mutex(&(philo->data->lastmeal_lock), \
	"data->lastmeal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lock_mutex(&philo->data->eaten_meal_lock, \
	"philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->ate ++;
	if (unlock_mutex(&philo->data->eaten_meal_lock, \
	"philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data, philo->data->time_to_eat) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	eating(t_threads *philo)
{
	if (lock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (last_meal_time(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (unlock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	thinking(t_threads *philo)
{
	if (check_all_alive(philo->data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (print_action(philo->data, THINKING, philo->id))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	sleeping(t_threads *philo)
{
	if (print_action(philo->data, SLEEPING, philo->id))
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data, philo->data->time_to_sleep) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
