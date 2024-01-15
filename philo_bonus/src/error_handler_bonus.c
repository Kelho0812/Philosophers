/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/11 11:16:12 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	error_handler(t_errorcode error)
{
	if (error == WRONG_ARG_NR)
	{
		printf(RED "Error: Wrong number of arguments\n");
		printf(GRN "Try ./philo 4 410 200 200 [5]\n" RESET);
	}
	if (error == WRONG_CHARS)
	{
		printf(RED "Error: Arguments are not numbers\n");
		printf("Make sure not to use negatives or spaces\n");
		printf(GRN "Try ./philo 4 410 200 200 [5]\n" RESET);
	}
	if (error == MALLOC_PHILO)
		printf(RED "Error: Philosophers Malloc Invalid\n" RESET);
	if (error == MALLOC_FORKS)
		printf(RED "Error: Forks Malloc Invalid\n" RESET);
	if (error == WRONG_PID)
		printf(RED "Error: Forks Malloc Invalid\n" RESET);
	return (0);
}

void	ft_exit(t_data *data)
{
	usleep(700000);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_FORKS);
	free(data->philos);
}
