/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 12:36:06 by jorteixe         ###   ########.fr       */
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
	sem_t	*forks;
	sem_t	*dead;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEAD);
	forks = sem_open(SEM_FORKS, O_CREAT, 0600, data->nbr_philos);
	dead = sem_open(SEM_DEAD, O_CREAT, 0600, 1);
	i = 0;
	while (i < data->nbr_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->is_full = false;
		philo->is_dead = false;
		philo->last_meal_time = 0;
		philo->start_time = 0;
		philo->meals_eaten = 0;
		philo->data = data;
		i++;
	}
	sem_close(forks);
	sem_close(dead);
	return (1);
}
