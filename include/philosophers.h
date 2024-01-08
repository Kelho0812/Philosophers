/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:09:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/08 12:16:23 by jorteixe         ###   ########.fr       */
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
# include <time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	long long		last_meal_time;
	int				meals_eaten;
	int				status;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
	struct s_data	*data;

}					t_philo;
typedef struct s_data
{
	int				n_phil;
	bool			finish;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
	long long		start_time;
	long long		current_time;
	t_philo			*philos;
}					t_data;

/********************/
/*		STATUS		*/
/********************/

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define ALIVE 4
# define DEAD 5

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
/*		ERRORS		*/
/********************/

# define WRONG_ARG 1
# define WRONG_CHARS 2
# define INVALID_TIME 3
# define PHIL_MALLOC 4

int					error_handler(int error, void *param, void **param2);
void				ft_exit(t_data *data);

/********************/
/*		UTILS		*/
/********************/
void				initializer(t_data *data, char **argv);
long				ft_atoi_change(const char *str);
int					ft_isdigit(int n);
void				num_checker(char **argv);
void				monitor(t_data *data);

/********************/
/*		TIME		*/
/********************/

long long			get_current_time(void);
int					ft_usleep(long long milliseconds);

/********************/
/*		PHILOS		*/
/********************/

void				initialize_philos(t_data *data);
void				threads_create(t_data *data);
void				threads_join(t_data *data);
void				eating(t_philo *philo);

#endif