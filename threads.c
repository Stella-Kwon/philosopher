/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 23:05:41 by sukwon            #+#    #+#             */
/*   Updated: 2024/06/27 10:51:16 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->num_philos)
	{
		pthread_create(&(data->philos[i]), NULL, function, parameter for functoin);
	}
}

void	wait_threads(t_data *data)
{
	
}