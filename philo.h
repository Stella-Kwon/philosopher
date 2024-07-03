#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef int bool;

#define true 1
#define false 0

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
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	int eaten_meal_count;
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
	pthread_mutex_t alive_mutex;
	pthread_mutex_t print_lock;
	pthread_mutex_t *forks; // 그냥 어쩌면 이거자체가 forks의 의미지
	int init_time;
	int timestamps;
	struct s_threads *philos;
	pthread_t monitor;
} t_data;

// initializer
int philos_init(t_data *data);
int data_philos_init(t_data *data, char **argv);

// get_time
int get_time();
int get_elapsed_time(t_data *data);

// print_shell
int print_action(t_data *data, int actions, int philo);
// int error_print(char *msg);

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
int wait_threads(t_data *data);

// routines
void *philo_routine(void *data);

// monitor
void monitoring(void *data);
int death_check(t_data *data);
#endif