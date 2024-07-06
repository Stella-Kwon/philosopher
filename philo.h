/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sukwon <sukwon@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:11:30 by sukwon            #+#    #+#             */
/*   Updated: 2024/07/06 22:34:00 by sukwon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

enum e_actions
{
	TAKEN_FORKS,
	EATING,
	THINKING,
	SLEEPING,
	DIED
};

typedef struct s_threads
{
	int				id;
	pthread_t		philo;
	size_t			last_meal;
	t_bool			left_f;
	t_bool			right_f;
	int				ate;
	struct s_data	*data;

}	t_threads;

typedef struct s_data
{
	size_t				num_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					must_eat_count;
	size_t				init_time;
	t_bool				all_alive;
	pthread_mutex_t		alive_lock;
	pthread_mutex_t		eaten_meal_lock;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		lastmeal_lock;
	pthread_mutex_t		*forks;
	struct s_threads	*philos;
	pthread_t			monitor;
}	t_data;

int		ft_atoi(const char *str);
int		check_valid_args(int argc, char **argv);
int		data_philos_init_whole(t_data *data, char **argv);
size_t	get_time(void);
int		print_action(t_data *data, int actions, int philo);
int		error_print(char *msg);
int		unlock_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int		lock_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int		init_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int		destroy_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int		rm_all_mutex(t_data *data);
void	malloc_free(t_data *data);
int		create_thread_philos(t_data *data);
int		detach_thread_philos(t_data *data);
int		wait_threads(t_data *data);
int		unlock_both_fork(t_threads *philo);
int		eating(t_threads *philo);
int		thinking(t_threads *philo);
int		sleeping(t_threads *philo);
void	*philo_routine(void *philos);
int		ft_usleep(t_data *data, size_t time);
int		check_all_alive(t_data *data);
void	*monitoring_death(void *d_data);
int		unlock_both_fork(t_threads *philo);
int		lock_both_fork(t_threads *philo);
#endif