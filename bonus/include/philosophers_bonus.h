/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:44:47 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/11 11:16:12 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h> /* For O_* constants */
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h> /* For mode constants */
# include <sys/time.h>
# include <sys/wait.h>
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

typedef struct s_data	t_data;

# define SEM_FORKS "/forks"
# define SEM_DEAD "/dead"
# define SEM_PHILO "/philo"

typedef struct s_philo
{
	pid_t				pid;
	pthread_t			philo_thread;
	int					id;
	long long			last_meal_time;
	long long			start_time;
	int					meals_eaten;
	bool				full;
	t_data				*data;
	sem_t				*forks_sem;
	sem_t				*dead_sem;
}						t_philo;
typedef struct s_data
{
	int					nbr_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					meals_to_eat;
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
int						initializer(t_data *data, int argc, char **argv);
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
void					processes_create(t_data *data);
void					eating(t_philo *philo);

/********************/
/*	GETTERS/SETTERS	*/
/********************/

void					set_bool(sem_t *sem, bool *bool_pointer, bool value);
bool					get_bool(sem_t *sem, bool *bool_pointer);
void					set_long_long(sem_t *sem, long long *llpointer,
							long long value);
long long				get_long_long(sem_t *sem, long long *llpointer);
bool					dinner_finished(t_data *data);

#endif