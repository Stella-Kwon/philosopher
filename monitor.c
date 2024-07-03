/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:42:31 by skwon2            #+#    #+#             */
/*   Updated: 2024/07/03 14:57:12 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_check(t_data *data)
{
    // if (data->num_philos > 200)
    //     return (EXIT_FAILURE);
    int i;

    i = 0;
    while (i < data->num_philos)
    {
        if (data->philos[i].last_meal != data->init_time)
        {
            if (data->philos[i].last_meal - data->timestamps >= data->time_to_die)
            {
                print_action(data, DIED, data->philos[i].id);
                return (EXIT_FAILURE);
            }
            else
            {
                data->
            }
            i++;
        }
    }
    return (EXIT_FAILURE);
}

void monitoring(t_data *data)
{
    while (data->all_alive)
    {
    }
}