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

#include "../include/philosophers.h"

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
	return (0);
}

void	ft_exit(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_destroy(&data->philos[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	free(data->philos);
	free(data->forks);
}