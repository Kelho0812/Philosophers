/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:06:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 11:03:32 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_handler(int error, void *param, void **param2)
{
	(void) param;
	(void) param2;
	if (error == WRONG_ARG)
	{
		printf("Wrong num of Arguments\n");
		printf("Please write: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat] \n");
	}
	exit(1);
}