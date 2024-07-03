/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:00:11 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/03 14:55:16 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*philo_routine(void *data)
{
	t_data *data_s = (t_data *)data;
	while (data_s->all_alive)
	{
		if (0 < data_s->must_eat_count && data_s->must_eat_count == data_s->philos->eaten_meal_count)
			break;
		// if (death_check(data_s) == EXIT_FAILURE)
		// {
		// 	data_s->all_alive == false;
		// 	break;
		// }
			if (data_s->num_philos % 2 == 0)
				eating(data_s);
			else
			
				usleep(500);
			eating,
				먹고나면 꼭 체크해서 값다시 넣어주기
				if (data->philos[i].last_meal == -100)
					return (EXIT_FAILURE);
	}

}

int		eating(t_data *data)
{

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
