#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

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
	int				id;
	pthread_t		philo;
	int				last_meal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				eaten_meal_count;
	struct s_data	*data; //순환 참조 circular reference를 막기 위해 포인터로 불러오기

} t_threads;

typedef struct s_data
{
	int					num_philos;
    int					time_to_die;
    int					time_to_eat;
    int					time_to_sleep;
    int					must_eat_count;
	bool				all_alive; //TRUE or FALSE
	pthread_mutex_t		print_lock;
	pthread_mutex_t		*forks; // 그냥 어쩌면 이거자체가 forks의 의미지 
	int					init_time;
	int					timestamps;
	struct s_threads	*philos;
}	t_data;

// get_time
int	get_time();
int	get_elapsed_time(t_data *data);

// intializing
void	data_philos_init(t_data *data, char **argv);

//print_shell
void	print_action(t_data *data, int actions);



#endif