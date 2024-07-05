/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:00:11 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/05 19:47:33 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_data *data, size_t time)
{
	size_t	start;
	size_t	current;
	
	start = get_time();
	current = start;
	if (start == (size_t)-100)
		return (EXIT_FAILURE);
	while (current - start < time)
	// 데이터 접근 시에도 동기화를 위해 mutex를 사용해야 하는 이유는 여러 스레드가 동시에 같은 데이터에 접근할 때 발생할 수 있는 데이터 경합(data race)을 방지하기 위해서입니다. 
	{
		// printf("current :  %ld\n", current - start);
		if (check_alive_error(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		usleep(500); // PUT THIS LIKE THIS AND GAV -500 WHEN YOU PUTH HOW LONG YOU TIME TO EAT
		current = get_time();
		if (current == (size_t)-100)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_eat_count(t_data *data)
{
	size_t i;
	size_t  count;
	
	i = 0;
	count = 0;
	
	while (i++ < data->num_philos)
	{
		if (data->philos[i].ate == 1)
			count++;
		// printf("count : %ld\n", count);
	}
	if (count == data->num_philos)
	{
		if (lock_mutex(&data->eaten_meal_lock, "data->eaten_meal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		data->eaten_meal_count += 1;
		if (unlock_mutex(&data->eaten_meal_lock, "data->eaten_meal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	// printf("data->eaten_meal_count : %d\n", data->eaten_meal_count);
	return (EXIT_SUCCESS);
}

static int	eating_routine(t_threads *philo)
{
	if (philo->id % 2 == 0)
	{
		if (eating(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);	
	}
	else
	{
		if (ft_usleep(philo->data, philo->data->time_to_eat) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (eating(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);	
	}
	if (lock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_eat_count(philo->data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo->data->must_eat_count > 0 && philo->data->eaten_meal_count >= philo->data->must_eat_count)
        return EXIT_FAILURE;
	if (unlock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// printf("all_alive : %d\n", philo->data->all_alive);
	return (EXIT_SUCCESS);
}

static int all_actions_check_erorro_flag(t_threads *philo)
{
	// printf("all_alive : %d\n", philo->data->all_alive);
	if( eating_routine(philo) == EXIT_FAILURE)
    {
        if (lock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        philo->data->error_flag = true;
        if (unlock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
		return (EXIT_FAILURE);
    }
	// printf("all_alive : %d\n", philo->data->all_alive);
	if ( sleeping(philo) == EXIT_FAILURE)
    {
        if (lock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        philo->data->error_flag = true;
        if (unlock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
		return (EXIT_FAILURE);
    }
	// printf("all_alive : %d\n", philo->data->all_alive);
	if ( thinking(philo) == EXIT_FAILURE)
    {
        if (lock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        philo->data->error_flag = true;
        if (unlock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
		return (EXIT_FAILURE);
    }
	// printf("all_alive : %d\n", philo->data->all_alive);
	return (EXIT_SUCCESS);
}

int	check_alive_error(t_data *data)
{
	if (lock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (lock_mutex(&data->error_lock, "data->error_lock") == EXIT_FAILURE)
	{
		if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (data->all_alive == false || data->error_flag == true)
	{
		if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (unlock_mutex(&data->error_lock, "data->error_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (unlock_mutex(&data->error_lock, "data->error_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *philos)
{
	t_threads *philo;
	size_t i;
	
	philo = (t_threads *)philos;
	i = 0;
	while (1)
	{
		// printf("all_alive : %d\n", philo->data->all_alive);
		if (all_actions_check_erorro_flag(philo) == EXIT_FAILURE)
			break;
		//  printf("all_alive : %d\n", philo->data->all_alive);
		if (death_time_check(philo->data, i) == EXIT_FAILURE)
			break;
		// printf("all_alive : %d\n", philo->data->all_alive);
		// if (check_alive_error(philo->data) == EXIT_FAILURE)
		// 	break;
		i++;
		if (i >= philo->data->num_philos)
			i = 0;
		if (ft_usleep(philo->data, 1) == EXIT_FAILURE)
			break;
	}
	
	// printf("philosopher %d\n", philo->id);
	return (philos);
}