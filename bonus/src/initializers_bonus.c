/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/11 11:16:12 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	initializer(t_data *data, int argc, char **argv)
{
	if (!num_checker(argv))
		return (0);
	if (!data_init(data, argv, argc))
		return (0);
	if (!philos_init(data))
		return (0);
	return (1);
}

int	data_init(t_data *data, char **argv, int argc)
{
	data->nbr_philos = ft_atoi_change(argv[1]);
	data->time_to_die = ft_atoi_change(argv[2]);
	data->time_to_eat = ft_atoi_change(argv[3]);
	data->time_to_sleep = ft_atoi_change(argv[4]);
	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (argc == 6)
		data->meals_to_eat = ft_atoi_change(argv[5]);
	else
		data->meals_to_eat = -1;
	return (1);
}

int	philos_init(t_data *data)
{
	int		i;
	t_philo	*philo;
	

	i = 0;
	while (i < data->nbr_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->last_meal_time = 0;
		philo->meals_eaten = 0;
		philo->data = data;
		i++;
	}
	return (1);
}
