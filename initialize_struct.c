/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:18:23 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 17:24:12 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philos_init(t_data *data)
{
	size_t i;

	i = 0;
	data->philos = malloc(data->num_philos * sizeof(t_threads));
	if (data->philos == NULL)
		return (EXIT_FAILURE);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1; // 철학자 ID 설정 (1부터 시작)
		data->philos[i].last_meal = get_time(data); // 0이런걸로 해놓으면 나중에 time_to_die보다 더커져서 암튼 고생함
		if (data->philos[i].last_meal == (size_t)-100)
			return (EXIT_FAILURE);
		data->philos[i].ate = 0;
		// data->philos[i].ate_all = false;
		data->philos[i].data = data; // 자신이 속한 데이터 구조체 설정
		data->philos[i].right_f = false;
		data->philos[i].left_f = false;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int init_other_mutex(t_data *data)
{
	if (init_mutex(&data->eaten_meal_lock, "data->eaten_meal_lock") != 0)
		return (EXIT_FAILURE); //eaten_meal_lock 생성
	// data->eaten_meal_count = 0;
	if (init_mutex(&data->alive_lock, "data->alive_lock") != 0)
		return (EXIT_FAILURE); //alive_lock 생성
	data->all_alive = true; //초기 상태는 모두 생존으로 설정
	if (init_mutex(&data->print_lock, "data->print_lock") != 0)
		return (EXIT_FAILURE); //print_lock 생성
	if (init_mutex(&data->lastmeal_lock, "data->lastmeal_lock") != 0)
		return (EXIT_FAILURE); //lastmeal_lock 생성
	return (EXIT_SUCCESS);
}

static int	data_philos_init_first(t_data *data, char **argv)
{
	data->init_time = get_time(data); // 초기화된 시간 값, 제일 먼저 설정.
	if (data->init_time == (size_t)-100)
		return (EXIT_FAILURE);
	data->num_philos = (size_t)ft_atoi(argv[1]);
	data->time_to_die = (size_t)ft_atoi(argv[2]);
	data->time_to_eat = (size_t)ft_atoi(argv[3]);
	data->time_to_sleep = (size_t)ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1; // 지정된 횟수없다는 의미로 -1
	if (init_other_mutex(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	init_forks_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (init_mutex(&data->forks[i], "data->forks[i]") == EXIT_FAILURE)
		{
			while (i >= 0)
			{
				if (destroy_mutex(&data->forks[i], \
				"data->forks[i]") == EXIT_FAILURE)
					return (EXIT_FAILURE);
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	data_philos_init_whole(t_data *data, char **argv)
{
	if (data_philos_init_first(data, argv) == EXIT_FAILURE)
	{
		rm_all_mutex(data);
		return (EXIT_FAILURE);
	}
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
	{
		printf("malloc : ");
		return (EXIT_FAILURE);
	}
	if (init_forks_mutex(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (philos_init(data) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
