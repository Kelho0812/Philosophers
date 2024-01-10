/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:30:51 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 21:37:09 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// wait_philos(philo->data);
	while (!dinner_finished(philo->data))
	{
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
		write_action(THINKING, philo);
	}
	return (NULL);
}

void	dinner(t_data *data)
{
	if (data->meals_to_eat == 0)
		return ;
	else if (data->nbr_philos == 1)
		;
	else
		threads_create(data);
	set_long_long(&data->data_mutex, &data->start_time, get_current_time());
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
	pthread_mutex_lock(&philo->second_fork->fork);
	write_action(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->first_fork->fork);
	write_action(TAKE_SECOND_FORK, philo);
	set_long_long(&philo->philo_mutex, &philo->last_meal_time,
		get_current_time());
	philo->meals_eaten++;
	write_action(EATING, philo);
	ft_usleep(philo->data->time_to_eat);
	if (philo->data->meals_to_eat > 0
		&& philo->meals_eaten == philo->data->meals_to_eat)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
	}
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
}

// void	monitor(t_data *data)
// {
// 	long long	now;
// 	int			i;
// 	int			time_passed;

// 	i = 0;
// 	while (i < data->n_phil)
// 	{
// 		now = get_current_time();
// 		data->current_time = now;
// 		time_passed = now - data->philos[i].last_meal_time;
// 		if (time_passed > data->time_to_die && data->philos->status != EATING)
// 		{
// 			printf(RED "%d %d died\n" RESET, time_passed, data->philos[i].id);
// 			data->philos[i].status = DEAD;
// 			data->finish = true;
// 			break ;
// 		}
// 		if (data->philos[i].meals_eaten == data->n_meals
// 			&& data->philos[i].checked == false)
// 		{
// 			data->nr_full++;
// 			data->philos[i].checked = true;
// 		}
// 		i++;
// 	}
// 	if (data->nr_full == data->n_phil)
// 		data->finish = true;
// }

void	write_action(t_status status, t_philo *philo)
{
	long long	time_passed;

	time_passed = get_current_time() - get_long_long(&philo->data->data_mutex, &philo->data->start_time);
	if (philo->full)
		return ;
	else
	{
		pthread_mutex_lock(&philo->data->write_mutex);
		if (!dinner_finished(philo->data))
		{
			if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
				printf(WHT "%lld" YEL " %d has taken a fork\n" RESET,
					time_passed, philo->id);
			else if (status == SLEEPING)
				printf(WHT "%lld" RESET " %d is sleeping\n", time_passed,
					philo->id);
			else if (status == THINKING)
				printf(WHT "%lld" RESET " %d is thinking\n", time_passed,
					philo->id);
			else if (status == EATING)
				printf(WHT "%lld" CYN " %d is eating\n" RESET, time_passed,
					philo->id);
			else if (status == DEAD)
				printf(RED "%lld %d died\n" RESET, time_passed, philo->id);
		}
		pthread_mutex_unlock(&philo->data->write_mutex);
	}
}
