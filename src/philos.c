/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:10:51 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/08 11:20:55 by jorteixe         ###   ########.fr       */
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
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->philos[i].right_fork, NULL);
		data->philos[i].left_fork = &data->philos[i + 1].right_fork;
		data->philos[i].data = data;
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->finish != true)
	{
		printf("%d %d thinking\n", philo->id);
		philo->status = THINKING;
		printf("%d %d sleeping\n", philo->id);
		philo->status = SLEEPING;
		ft_usleep(philo->time_to_sleep);
		eating(philo);
	}
	return (NULL);
}

void	threads_create(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		pthread_create(&(data->philos[i].thread), NULL, &routine,
			&(data->philos[i]));
		i++;
	}
}

void	threads_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_phil)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&(philo->right_fork));
	philo->status = EATING;
	philo->last_meal_time = get_current_time();
	philo->meals_eaten += 1;
	ft_usleep(philo->time_to_eat);
}
