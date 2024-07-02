/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:00:11 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/02 16:42:12 by skwon2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_routine(t_data *data)
{
	while (data->all_alive)
	{
		
		if (data->num_philos % 2 == 0)
			eating
		else 
			wait,
			eating,
		
	}

}

int		eating(t_data *data)
{
	// if (death_check(data))
	// 	retrun (EXIT_FAILURE); monitor will proceed

	unll
}

int		thinking(t_data *data)
{

}

int		sleep(t_data	*data)
{
	
}

int		put_in_waiting(t_data	*data)
{
	
}

int		death_check(t_data	*data)
{
	if (data->num_philos > 200)
		return (EXIT_FAILURE);
	if (data->philos->last_meal != data->init_time)
	{
		if (data->timestamps - data->philos->last_meal > data->time_to_die)
			return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}