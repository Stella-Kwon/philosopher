/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suminkwon <suminkwon@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:16:54 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/03 14:50:42 by suminkwon        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time()
{
    struct timeval time; 
	// tv_sec: 이 필드는 Epoch 시점(1970년 1월 1일 00:00:00 UTC)부터 현재까지의 초 단위 시간을 나타냅니다.
	// tv_usec: 이 필드는 초 단위 시간의 나머지 부분을 마이크로초 단위로 나타냅니다.
    if (gettimeofday(&time, NULL) == -1)
	{
		printf("gettimeofday is failed\n");
		return (-100);
	}
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// int	get_elapsed_time(t_data *data)
// {
// 	if (get_time == -100)
// 		return (EXIT_FAILURE);
// 	}
// 	(data)->timestamps = get_time() - (data)->init_time;
// 	return(data->timestamps);
// }
