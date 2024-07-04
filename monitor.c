/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:42:31 by skwon2            #+#    #+#             */
/*   Updated: 2024/07/05 02:16:57 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_time_check(t_data *data, int i)
{
    int time;

    time = get_time_check(data);
    if (time == -100)
        return (EXIT_FAILURE);
    if (lock_mutex(&(data->philos[i].lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (data->philos[i].last_meal != data->philos[i].data->init_time && \
    time - data->philos[i].last_meal >= data->philos[i].data->time_to_die)
    {
        if (lock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        data->all_alive = false;
        if (unlock_mutex(&data->alive_lock, "data->alive_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (lock_mutex(&(data->print_lock), "data->print_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (print_action(data, DIED, data->philos[i].id) == EXIT_FAILURE)
            return (EXIT_FAILURE);

        if (unlock_mutex(&(data->print_lock), "data->print_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    if (unlock_mutex(&(data->philos[i].lastmeal_lock), "data->lastmeal_lock") == EXIT_FAILURE)
            return EXIT_FAILURE;
    return (EXIT_SUCCESS);
}

int get_time_check(t_data *data)
{
    int time;
    
    time = get_time(data);
    if (time == -100)
    {
        if (lock_mutex(&data->error_lock, "data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        data->error_flag = true;
        if (unlock_mutex(&data->error_lock, "data->error_lock") == EXIT_FAILURE)
            return (EXIT_FAILURE);
        return (EXIT_FAILURE);
    }
    return (time);
}

void *monitoring_death(void *d_data)
{
    t_data *data;
    int i;
    
    data = (t_data *)d_data;
    i = 0;
    while (1)
    {
        // if (death_time_check(data, i) == EXIT_FAILURE)
        //     break;
        if (check_alive_error(data) == EXIT_FAILURE)
			break;

        i++;
        if (i >= data->num_philos)
            i = 0;
        if (ft_usleep(data, 1) == EXIT_FAILURE)
            break;
    }
    return (NULL);
}

// Sleep to reduce CPU usage
// usleep(500);
/*
usleep을 사용하는 것은 CPU가 놀고 있는 시간 동안 
다른 스레드나 프로세스가 CPU 자원을 받아 사용할 수 있도록 하는 것입니다. 
이로 인해 시스템 전체의 반응성이 향상되며,
여러분의 애플리케이션이 CPU 자원을 독점하는 것을 방지합니다.

보다 자세히 설명하자면, 
usleep은 작은 시간 동안 현재 스레드를 대기 상태로 전환시킵니다. 
이렇게 함으로써 CPU는 현재 스레드의 작업 외에도 
다른 스레드나 프로세스에게 할당될 수 있는 기회를 얻습니다. 
만약 usleep이 없다면, CPU는 루프가 빠르게 반복되는 동안 지속적으로 
현재 스레드에 할당되어 다른 스레드나 프로세스에게 CPU 자원을 줄 수 없습니다. 

이는 시스템 전반의 반응성을 저하시키고, 
다른 프로세스들이 제 시간에 작업을 처리하지 못하게 만들 수 있습니다.

따라서 usleep을 사용함으로써 CPU 자원을 보다 공정하게 분배할 수 있고, 
시스템이 더 나은 성능과 반응성을 발휘할 수 있도록 돕습니다.
*/