/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:55:38 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 17:30:44 by sukwon           ###   ########.fr       */
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
	while (current - start <= time)
	{
		if (check_all_alive(data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = get_time();
		if (current == (size_t)-100)
			return (EXIT_FAILURE);
		usleep(500);
	}
	return (EXIT_SUCCESS);
}

void	*philo_routine(void *philos)
{
	t_threads *philo;
	
	philo = (t_threads *)philos;
	if (philo->data->must_eat_count == 0)
		return (philo);
	if (philo->id % 2 == 0)
	{
		if (ft_usleep(philo->data, philo->data->time_to_eat) == EXIT_FAILURE)
			return (philos);
	}
	
	while (1)// 모니터링이랑은 별개로 이렇게 해야 (사실 모든 액션에 다 check_all_alive가 있음) 각 스레드가 죽어 all_alive == false일떄
	{
		if (check_all_alive(philo->data) == EXIT_FAILURE)
			break;
		if (eating(philo) == EXIT_FAILURE)
			break;
		if (sleeping(philo) == EXIT_FAILURE)
			break;
		if (thinking(philo) == EXIT_FAILURE)
			break;
		// if (ft_usleep(philo->data, 10) == EXIT_FAILURE)
		// 	break;
	}
	unlock_both_fork(philo);
	return (philos);
}