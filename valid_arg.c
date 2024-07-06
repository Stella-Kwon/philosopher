/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:45:18 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 22:38:15 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_valid_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (error_print("Prompt should be like this :\n ./philo <philo_count> \
		<time_to_die> <time_to_eat> <time_to_sleep> [times_each_must_eat]\n"));
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > INT_MAX)
		return (error_print("Invalid number of philosophers"));
	if (ft_atoi(argv[2]) <= 0)
		return (error_print("Positive number required for time_to_die"));
	if (ft_atoi(argv[3]) <= 0)
		return (error_print("Positive number required for time_to_eat"));
	if (ft_atoi(argv[4]) <= 0)
		return (error_print("Positive number required for time_to_sleep"));
	if (argv[5] && ft_atoi(argv[5]) < 0)
		return (error_print("should be more than 0 amout"));
	return (0);
}
