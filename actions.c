/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:14:36 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 21:47:23 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		unlock_both_fork(t_threads *philo)
{
	int right_index;
	int left_index;

	left_index = philo->id - 1;
	right_index = (philo->id - 2 + philo->data->num_philos) % philo->data->num_philos;
	
	if (philo->right_f == true)
	{
		philo->right_f = false;
		if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	if (philo->left_f == true)
	{
		philo->left_f = false;
		if (unlock_mutex(&philo->data->forks[left_index], "philo->data->forks[left_index]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);	
}

int	lock_both_fork(t_threads *philo)
{
	int right_index;
	int left_index;

	left_index = philo->id - 1;
	right_index = (philo->id - 2 + philo->data->num_philos) % philo->data->num_philos;
	// printf("right\n");
	if (lock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->right_f = true;
	if (print_action(philo->data, TAKEN_FORKS, philo->id, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo->data->num_philos == 1)
		return (EXIT_FAILURE);
	// printf("left\n");
	if (lock_mutex(&philo->data->forks[left_index], "philo->data->forks[left_index]") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->left_f = true;
	if  (print_action(philo->data, TAKEN_FORKS, philo->id, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (print_action(philo->data, EATING, philo->id, NULL) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);	
}

int last_meal_time(t_threads *philo)
{
	if (lock_mutex(&(philo->data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
        return (EXIT_FAILURE);
	philo->last_meal = get_time();
	if (philo->last_meal == (size_t)-100)
	{
		if (unlock_mutex(&philo->data->lastmeal_lock, "data->lastmeal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	// printf("lastmeal time : %zu\n", philo->last_meal);
	if (unlock_mutex(&(philo->data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
        return (EXIT_FAILURE);
	//여기다 가바로해줘야해 포크들고 먹기 시간 주기전에
	if (lock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	philo->ate ++;
	// print_action(philo->data, -1, philo->ate, NULL);
	if (unlock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
    if (ft_usleep(philo->data, philo->data->time_to_eat) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		eating(t_threads *philo)
{
	if (lock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (last_meal_time(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//여기다 두면 eating이 더 여러번 프린팅 된다 시간차떄매
	// if (lock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);
	// philo->ate ++;
	// // print_action(philo->data, -1, philo->ate, NULL);
	// if (unlock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	if (unlock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

int		thinking(t_threads *philo)
{
	if (check_all_alive(philo->data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (print_action(philo->data, THINKING, philo->id, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		sleeping(t_threads *philo)
{
	if (print_action(philo->data, SLEEPING, philo->id, NULL))
		return (EXIT_FAILURE);
	if (ft_usleep(philo->data, philo->data->time_to_sleep) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (check_all_alive(philo->data) == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
