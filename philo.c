/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:20:25 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/04 12:12:34 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char	**argv)
{
	t_data		data;

	if (check_valid_args(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (data_philos_init_whole(&data, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (create_thread_philos(&data) == EXIT_FAILURE)
	{
		rm_all_mutex(&data);
		return (EXIT_FAILURE);
	}
	if (wait_threads(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (rm_all_mutex(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	malloc_free(&data);
	return (0);
}
