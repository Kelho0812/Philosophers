/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:09:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 11:02:40 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int	n_phil;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	long long	n_meals;
}		t_data;

typedef struct s_phil
{
	int	id;
	long long last_meal_time;
	pthread_mutex_t left_fork;
	pthread_mutex_t *right_fork;

}		t_phil;

/********************/
/*		ERRORS		*/
/********************/

# define WRONG_ARG 1

int	error_handler(int error, void *param, void **param2);


/********************/
/*		TIME		*/
/********************/

long long get_current_time();


#endif