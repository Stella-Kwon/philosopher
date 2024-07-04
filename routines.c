/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:00:11 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/05 02:19:34 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(t_data *data, int time)
{
	int	start;
	int	current;
	
	start = get_time_check(data);
	current = get_time_check(data);
	if (start == -100 || current == -100)
		return (EXIT_FAILURE);
	while (current - start < time)
	// 데이터 접근 시에도 동기화를 위해 mutex를 사용해야 하는 이유는 여러 스레드가 동시에 같은 데이터에 접근할 때 발생할 수 있는 데이터 경합(data race)을 방지하기 위해서입니다. 
	{
		if (check_alive_error(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		// usleep(500);
		current = get_time_check(data);
		if (current == -100)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	eating_routine(t_threads *philo)
{
	if (philo->data->num_philos % 2 == 0)
	{
		if (eating(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);	
	}
	else
	{
		if (ft_usleep(philo->data, 1) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (eating(philo) == EXIT_FAILURE)
			return (EXIT_FAILURE);	
	}
	
	if (lock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (lock_mutex(&(philo->data->eaten_meal_lock), "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo->data->eaten_meal_count += 1;
	printf("philo->eaten_meal_count : %d\n",philo->data->eaten_meal_count);
	if (unlock_mutex(&(philo->data->eaten_meal_lock), "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (unlock_mutex(&(philo->data->print_lock), "philo->data->print_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);

	
	return (EXIT_SUCCESS);
}

static int all_actions_check_erorro_flag(t_threads *philo)
{
	if(eating_routine(philo) == EXIT_FAILURE)
    {
        if (lock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        philo->data->error_flag = true;
        if (unlock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
		return (EXIT_FAILURE);
    }
	//변경되는 값이 아니라서 mutex안쓰고 philo->data로 들어가서 데이터에 접근하면 mutex없어도 가능
	if (lock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philo->data->must_eat_count > 0 && philo->data->eaten_meal_count >= philo->data->must_eat_count)
        return EXIT_FAILURE;
	if (unlock_mutex(&philo->data->eaten_meal_lock, "philo->data->eaten_meal_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (sleeping(philo) == EXIT_FAILURE)
    {
        if (lock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        philo->data->error_flag = true;
        if (unlock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
		return (EXIT_FAILURE);
    }
	if (thinking(philo) == EXIT_FAILURE)
    {
        if (lock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        philo->data->error_flag = true;
        if (unlock_mutex(&philo->data->error_lock, "philo->data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
		return (EXIT_FAILURE);
    }
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
	int i;
	
	philo = (t_threads *)philos;
	i = 0;
	while (1)
	{
		if (all_actions_check_erorro_flag(philo) == EXIT_FAILURE)
			break;
		if (death_time_check(philo->data, i) == EXIT_FAILURE)
			break;
		if (check_alive_error(philo->data) == EXIT_FAILURE)
			break;
		i++;
		if (i >= philo->data->num_philos)
			i = 0;
		if (ft_usleep(philo->data, 1) == EXIT_FAILURE)
			break;
	}
	return (philos);
}