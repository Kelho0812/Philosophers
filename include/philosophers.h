/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:09:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 17:44:31 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data
{
	int				n_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_meals;
}					t_data;

typedef struct s_phil
{
	int				id;
	long long		last_meal_time;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;

}					t_phil;

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

int					error_handler(int error, void *param, void **param2);

/********************/
/*		UTILS		*/
/********************/
void				arg_checker_parser(t_data *data, char **argv);
void				num_checker(char **argv);

/********************/
/*		TIME		*/
/********************/

long long			get_current_time(void);
int					ft_usleep(unsigned long long time);

#endif