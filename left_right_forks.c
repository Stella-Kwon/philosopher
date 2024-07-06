/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right_forks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:23:40 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 22:29:33 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	unlock_both_fork(t_threads *philo)
{
	int	right_index;
	int	left_index;

	left_index = philo->id - 1;
	right_index = (philo->id - 2 + philo->data->num_philos) \
	% philo->data->num_philos;
	if (philo->right_f == TRUE)
	{
		philo->right_f = FALSE;
		if (unlock_mutex(&philo->data->forks[right_index], \
		"philo->data->forks[right_index]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (philo->left_f == TRUE)
	{
		philo->left_f = FALSE;
		if (unlock_mutex(&philo->data->forks[left_index], \
		"philo->data->forks[left_index]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	lock_both_fork(t_threads *philo)
{
	int	right_index;
	int	left_index;

	left_index = philo->id - 1;
	right_index = (philo->id - 2 + philo->data->num_philos) \
	% philo->data->num_philos;
	if (lock_mutex(&philo->data->forks[right_index], \
	"philo->data->forks[right_index]") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->right_f = TRUE;
	if (print_action(philo->data, TAKEN_FORKS, philo->id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo->data->num_philos == 1)
		return (EXIT_FAILURE);
	if (lock_mutex(&philo->data->forks[left_index], \
	"philo->data->forks[left_index]") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->left_f = TRUE;
	if (print_action(philo->data, TAKEN_FORKS, philo->id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (print_action(philo->data, EATING, philo->id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
