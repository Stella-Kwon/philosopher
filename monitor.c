/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:15:43 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 21:46:44 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_all_alive(t_data *data)
{
	if (lock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	
	if (data->all_alive == false)
	{
		// printf("data->all_alive : %d\n", data->all_alive);
		if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
    if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int death_timeout(t_data *data)
{
	size_t i;
	size_t time;

	i = 0;
	time = get_time();
    if (time == (size_t)-100)
        return (EXIT_FAILURE);
	while (i < data->num_philos)
	{
		if (lock_mutex(&(data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
        	return (EXIT_FAILURE);
		if (time - data->philos[i].last_meal > data->philos[i].data->time_to_die)
		{
			// printf("time : %zu\n lastmeal_time : %zu \n philo->%d from lastmeal : %zu\n", time, data->philos[i].last_meal, data->philos[i].id, time - data->philos[i].last_meal );
			if (unlock_mutex(&(data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
				return EXIT_FAILURE;
			if (print_action(data, DIED, data->philos[i].id, NULL) == EXIT_FAILURE)
            	return (EXIT_FAILURE);
			if (lock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
				return (EXIT_FAILURE);
			data->all_alive = false;
			if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
				return (EXIT_FAILURE);

			return (EXIT_FAILURE);
		}
		if (unlock_mutex(&(data->lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
			return EXIT_FAILURE;
		i++;
		
	}
	usleep(1000); // 여기다가 해줘야지 제일 lastmeal_time 동기화 오류가 안난다.
	return (EXIT_SUCCESS);
}

int	meal_count_timeout(t_data *data)
{
	size_t i;
	size_t  count;

	i = 0;
	count = 0;
	while (i < data->num_philos && data->must_eat_count != -1)
	{
		if (lock_mutex(&data->eaten_meal_lock, "data->eaten_meal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (data->philos[i].ate >= data->must_eat_count)
			count += 1 ;
		if (unlock_mutex(&data->eaten_meal_lock, "data->eaten_meal_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (count == data->num_philos) // 이말은 모든 philo가 data->must_eat_count보다 다 넘게 했다는 야기
	{
		// printf("count : %zu\n", count);
		if (lock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		data->all_alive = false;
		if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
			return (EXIT_FAILURE);
		return (EXIT_FAILURE);	
	}
	return (EXIT_SUCCESS);
}

void *monitoring_death(void *d_data)
{
    t_data *data;

    data = (t_data *)d_data;
	if (data->must_eat_count == 0)
		return (d_data);
    while (1)
    {
		if (death_timeout(data) == EXIT_FAILURE)
			break;
        if (meal_count_timeout(data) == EXIT_FAILURE)
			break;
    }
    return (d_data);
}
