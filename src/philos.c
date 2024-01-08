/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:10:51 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/08 12:19:18 by jorteixe         ###   ########.fr       */
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
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].status = ALIVE;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		pthread_mutex_init(&data->philos[i].right_fork, NULL);
		if (i == (data->n_phil - 1))
			data->philos[i].left_fork = &data->philos[0].right_fork;
		else
			data->philos[i].left_fork = &data->philos[i + 1].right_fork;
		data->philos[i].data = data;
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;
	
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
	{
		printf("%lld %d is thinking\n", philo->data->current_time - philo->data->start_time,
			philo->id);
		ft_usleep(1);
	}
	while (philo->data->finish != true)
	{
		eating(philo);
		printf("%lld %d is thinking\n", philo->data->current_time - philo->data->start_time,
			philo->id);
		philo->status = THINKING;
		printf(CYN "%lld %d is sleeping\n" RESET, philo->data->current_time - philo->data->start_time,
			philo->id);
		philo->status = SLEEPING;
		ft_usleep(philo->time_to_sleep);
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
	printf(YEL "%lld %d has taken a fork\n" RESET, philo->data->current_time
		- philo->data->start_time, philo->id);
	philo->status = EATING;
	philo->last_meal_time = philo->data->current_time;
	printf(GRN "%lld %d is eating\n" RESET, philo->data->current_time
		- philo->data->start_time, philo->id);
	philo->meals_eaten += 1;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
}
