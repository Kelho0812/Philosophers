/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:30:53 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 21:37:09 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/********************/
/*		COLORS		*/
/********************/

# define RED "\x1B[31m"
# define GRN "\x1B[32m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define WHT "\x1B[37m"
# define RESET "\x1B[0m"

/********************/
/*		STRUCTS		*/
/********************/

typedef pthread_mutex_t	t_mtx;
typedef struct s_data	t_data;
typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	long long			last_meal_time;
	int					meals_eaten;
	bool				full;
	t_mtx				philo_mutex;
	t_fork				*second_fork;
	t_fork				*first_fork;
	t_data				*data;
}						t_philo;
typedef struct s_data
{
	int					nbr_philos;
	int					nbr_threads_running;
	int					full_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_to_eat;
	long long			start_time;
	bool				finish;
	bool				threads_are_ready;
	pthread_t			monitor;
	t_mtx				data_mutex;
	t_mtx				write_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_data;

/********************/
/*		STATUS		*/
/********************/

typedef enum e_status
{
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
}						t_status;

/********************/
/*		ERRORS		*/
/********************/

typedef enum e_errorcode
{
	WRONG_ARG_NR,
	WRONG_CHARS,
	INVALID_TIME,
	MALLOC_PHILO,
	MALLOC_FORKS
}						t_errorcode;

int						error_handler(t_errorcode error);
void					ft_exit(t_data *data);

/********************/
/*		UTILS		*/
/********************/
int						initializer(t_data *data, char **argv, int argc);
int						data_init(t_data *data, char **argv, int argc);
long					ft_atoi_change(const char *str);
int						ft_isdigit(int n);
int						num_checker(char **argv);
void					*monitor(void *data);
void					write_action(t_status status, t_philo *philo);

/********************/
/*		TIME		*/
/********************/

long long				get_current_time(void);
int						ft_usleep(long long milliseconds);
void					wait_philos(t_data *data);

/********************/
/*		PHILOS		*/
/********************/

int						philos_init(t_data *data);
void					dinner(t_data *data);
void					threads_create(t_data *data);
void					threads_join(t_data *data);
void					eating(t_philo *philo);

/********************/
/*		MONITOR		*/
/********************/

bool					all_threads_running(t_mtx *mutex, int *thread_nbr,
							int philo_nbr);
void					increase_threads_running_nbr(t_mtx *mutex, int *value);

/********************/
/*	GETTERS/SETTERS	*/
/********************/

void					set_bool(t_mtx *mutex, bool *bool_pointer, bool value);
bool					get_bool(t_mtx *mutex, bool *bool_pointer);
void					set_long_long(t_mtx *mutex, long long *llpointer,
							long long value);
long long				get_long_long(t_mtx *mutex, long long *llpointer);
bool					dinner_finished(t_data *data);

#endif