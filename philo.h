#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef int bool;

# define true 1
# define false 0

enum actions
{
	TAKEN_FORKS,
	EATING,
	THINKING,
	SLEEPING,
	DIED
};

typedef struct s_threads
{
	int id;
	pthread_t philo;
	int last_meal;
	pthread_mutex_t lastmeal_lock;
	struct s_data *data; // 순환 참조 circular reference를 막기 위해 포인터로 불러오기

} t_threads;

typedef struct s_data
{
	int num_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;
	bool all_alive; // TRUE or FALSE
	bool error_flag; // TRUE or FALSE
	pthread_mutex_t alive_lock;
	pthread_mutex_t error_lock;
	pthread_mutex_t eaten_meal_lock;
	pthread_mutex_t print_lock;
	pthread_mutex_t *forks; // 그냥 어쩌면 이거자체가 forks의 의미지
	int init_time;
	// int timestamps;
	int eaten_meal_count;
	struct s_threads *philos;
	pthread_t monitor;
} t_data;


//utils
int	ft_atoi(const char *str);

//check_valid_args
int	check_valid_args(int argc, char **argv);

// initializer
int	data_philos_init_whole(t_data *data, char **argv);

// get_time
int get_time();

// print_shell
int print_action(t_data *data, int actions, int philo);
int	error_print(char *msg);

// mutex
int unlock_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int lock_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int init_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int destroy_mutex(pthread_mutex_t *mutex, char *name_of_mutex);
int rm_all_mutex(t_data *data);

// free malloc
void malloc_free(t_data *data);

// threads
int create_thread_philos(t_data *data);
int detach_thread_philos(t_data *data);
int wait_threads(t_data *data);

//actions
int		eating(t_threads *philo);
int		thinking(t_threads *philo);
int		sleeping(t_threads *philo);


// routines
void	*philo_routine(void *philos);
int	ft_usleep(t_data *data, int time);
int	check_alive_error(t_data *data);

// monitor
void    *monitoring_death(void *d_data);
int get_time_check(t_data *data);
int death_time_check(t_data *data, int i);

#endif