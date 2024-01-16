/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:30:51 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 11:28:54 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_philos(philo->data);
	set_long_long(&philo->philo_mutex, &philo->last_meal_time,
		get_current_time());
	increase_threads_running_nbr(&philo->data->data_mutex,
		&philo->data->nbr_threads_running);
	while (!dinner_finished(philo->data))
	{
		write_action(THINKING, philo);
		ft_usleep(1);
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	dinner(t_data *data)
{
	if (data->meals_to_eat == 0)
		return ;
	else if (data->nbr_philos == 1)
	{
		pthread_create(&(data->philos->thread), NULL, &routine_one,
			data->philos);
		pthread_join(data->philos->thread, NULL);
		return ;
	}
	else
		threads_create(data);
	set_long_long(&data->data_mutex, &data->start_time, get_current_time());
	pthread_create(&data->monitor, NULL, &monitor, data);
	set_bool(&data->data_mutex, &data->threads_are_ready, true);
	threads_join(data);
}

void	threads_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	threads_create(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		pthread_create(&(data->philos[i].thread), NULL, &routine,
			&(data->philos[i]));
		i++;
	}
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	write_action(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_action(TAKE_SECOND_FORK, philo);
	set_long_long(&philo->philo_mutex, &philo->last_meal_time,
		get_current_time());
	write_action(EATING, philo);
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	if (philo->data->meals_to_eat > 0
		&& philo->meals_eaten == philo->data->meals_to_eat)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
	}
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
}
