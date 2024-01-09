/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:51:26 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 16:30:05 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	distribute_forks(t_philo *philo, t_fork *forks, int i);

int	initializer(t_data *data, char **argv, int argc)
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
	data->start_time = get_current_time();
	data->finish = false;
	data->threads_are_ready = false;
	data->philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (data->philos == NULL)
		return (error_handler(MALLOC_PHILO));
	data->forks = malloc(sizeof(t_fork) * data->nbr_philos);
	if (data->forks == NULL)
	{
		free(data->philos);
		return (error_handler(MALLOC_FORKS));
	}
	pthread_mutex_init(&data->data_mutex, NULL);
	if (argc == 6)
		data->meals_to_eat = ft_atoi_change(argv[5]);
	else
		data->meals_to_eat = -1;
	init_forks_mutexes(data);
	return (1);
}

void	init_forks_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].fork_id = i;
		i++;
	}
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
		distribute_forks(philo, data->forks, i);
		i++;
	}
}

static void	distribute_forks(t_philo *philo, t_fork *forks, int philo_table_pos)
{
	int	philo_nbr;

	philo_nbr = philo->data->nbr_philos;
	if (!philo->id % 2)
	{
		philo->left_fork = &forks[(philo_table_pos + 1) % philo_nbr];
		philo->right_fork = &forks[philo_table_pos];
	}
	else
	{
		philo->right_fork = &forks[philo_table_pos];
		philo->left_fork = &forks[(philo_table_pos + 1) % philo_nbr];
	}
}
