/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:10:51 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/05 11:20:23 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	initialize_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_phil);
	if (!data->philos)
		error_handler(PHIL_MALLOC, NULL, NULL);
	i = 0;
	while (i < data->n_phil)
	{
		data->philos[i].id = i;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].status = ALIVE;
		pthread_mutex_init(&data->philos[i].left_fork, NULL);
		data->philos[i].right_fork = NULL;
		i++;
	}
}
