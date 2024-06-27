/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:18:23 by sukwon            #+#    #+#             */
/*   Updated: 2024/06/27 11:13:17 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_init(t_data *data)
{
	int i;

	i = 0;
	data->philos = malloc(data->num_philos * sizeof(t_threads));
	while (i++ < data->num_philos)
	{
		data->philos[i].id = i + 1; // 철학자 ID 설정 (1부터 시작)
		data->philos[i].last_meal = get_elapsed_time(data); // 초기화된 마지막 식사 시간 = 처음에는 0이라고 보면된다.
		data->philos[i].eaten_meal_count = 0;
		data->philos[i].data = data; // 자신이 속한 데이터 구조체 설정
		pthread_mutex_init(&data->philos[i].left_fork, NULL); // 왼쪽 포크 뮤텍스 초기화(생성이라고 보면 된다)
		pthread_mutex_init(&data->philos[i].right_fork, NULL); // 오른쪽 포크 뮤텍스 초기화(생성이라고 보면 된다)
	}
}

void	data_philos_init(t_data *data, char **argv)
{
	int	i;

	data->init_time = get_elapsed_time(data); // 초기화된 시간 값, 제일 먼저 설정.
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1; // 지정된 횟수없다는 의미로 -1
	data->all_alive = true; //초기 상태는 모두 생존으로 설정
	pthread_mutex_init(&data->print_lock, NULL); //print_lock 생성
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	i = 0;
	while (i++ < data->num_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	data->timestamps = data->init_time; // 초기화된 타임스탬프 값
	philos_init(data);
}
