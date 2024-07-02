/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skwon2 <skwon2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:42:38 by suminkwon         #+#    #+#             */
/*   Updated: 2024/07/02 16:42:22 by skwon2           ###   ########.fr       */
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