/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:42:38 by suminkwon         #+#    #+#             */
/*   Updated: 2024/06/28 15:43:02 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void malloc_free(t_data *data)
{
    if (data->forks)
    {
        free(data->forks);
        data->forks = NULL;
    }
    if (data->philos)
    {
        free(data->philos);
        data->philos = NULL;
    }
}