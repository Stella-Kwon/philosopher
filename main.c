/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:20:25 by sukwon            #+#    #+#             */
/*   Updated: 2024/06/27 10:44:57 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_data		data;

	data_philos_init(&data, argv);
	create_thread_philos(data);
	return (0);
}
