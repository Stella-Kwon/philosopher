/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:03:00 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/05 19:45:13 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		unlock_both_fork(t_threads *philo)
{
	int right_index;
	int left_index;

	left_index = philo->id - 1;
	right_index = (philo->id - 2 + philo->data->num_philos) % philo->data->num_philos;
	if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (unlock_mutex(&philo->data->forks[left_index], "philo->data->forks[left_index]") == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
	if (lock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
	{
		if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if  (print_action(philo->data, TAKEN_FORKS, philo->id) == EXIT_FAILURE)
	{
		 if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
        {
            if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
                return (EXIT_FAILURE);
        }
		if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
                return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
	{
		if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
                return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	// printf("left\n");
	if (lock_mutex(&philo->data->forks[left_index], "philo->data->forks[left_index]") == EXIT_FAILURE)
	{
		if (unlock_mutex(&philo->data->forks[right_index], "philo->data->forks[right_index]") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (lock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
	{
		if (unlock_both_fork(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if  (print_action(philo->data, TAKEN_FORKS, philo->id) == EXIT_FAILURE)
	{
		 if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
        {
			if (unlock_both_fork(philo) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			return (EXIT_FAILURE);
        }
		if (unlock_both_fork(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
	{
		if (unlock_both_fork(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (unlock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);	
}

int		eating(t_threads *philo)
{
	if (lock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
	{
		if (unlock_both_fork(philo) == EXIT_FAILURE)
            return EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if  (print_action(philo->data, EATING, philo->id) == EXIT_FAILURE)
	{
		 if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
        {
            if (unlock_both_fork(philo) == EXIT_FAILURE)
                return EXIT_FAILURE;
            
            return EXIT_FAILURE;
        }
        if (unlock_both_fork(philo) == EXIT_FAILURE)
            return EXIT_FAILURE;

	}
	if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
	{
		if (unlock_both_fork(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (lock_mutex(&(philo->data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
        return EXIT_FAILURE;
	philo->last_meal = get_time();
	// printf("eating _last_mead :%ld\n", philo->last_meal);
	if (philo->last_meal == (size_t)-100)
	{
		if (unlock_both_fork(philo) == EXIT_FAILURE)
		{
            if (unlock_mutex(&(philo->data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
                return EXIT_FAILURE;

            return EXIT_FAILURE;
        }
		return (EXIT_FAILURE);
	}
    if (unlock_mutex(&(philo->data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
            return EXIT_FAILURE;
    if (ft_usleep(philo->data, philo->data->time_to_eat-500) == EXIT_FAILURE)
	{
		if (unlock_both_fork(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (unlock_both_fork(philo) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->ate = 1;
	return (EXIT_SUCCESS);
}

int		thinking(t_threads *philo)
{
	// int thinking_time;

	// thinking_time = philo->data->time_to_die - (philo->data->time_to_sleep);
	// if (thinking_time > 0)
	// {
	// 	if (ft_usleep(philo->data, thinking_time) == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);
	// }
	// else
	// {
	// 	if (ft_usleep(philo->data, 1) == EXIT_FAILURE)
	// 		return (EXIT_FAILURE);
	// 	//usleep은 마이크로세컨드니까 1밀리세컨드 더 주면 알아서 thinking_time 오버되니까 die 되겠지?
	// }
	if (lock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (print_action(philo->data, THINKING, philo->id))
		return (EXIT_FAILURE);
	if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		sleeping(t_threads *philo)
{
	if (ft_usleep(philo->data, philo->data->time_to_sleep) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (print_action(philo->data, SLEEPING, philo->id))
		return (EXIT_FAILURE);
	if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
