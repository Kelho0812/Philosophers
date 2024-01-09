/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 11:10:51 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 17:03:48 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *) data;
	wait_philos(philo->data);
	while (!dinner_finished(philo->data))
	{
		/* code */
	}
	
	return (NULL);
}

void	dinner(t_data *data)
{
	if (data->meals_to_eat == 0)
		return;
	else if (data->nbr_philos == 1)
		;
	else
		threads_create(data);
	data->start_time = get_current_time();
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
	int i;

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
	pthread_mutex_lock(philo->left_fork);
	printf(YEL "%lld %d has taken a fork\n" RESET, philo->data->current_time
		- philo->data->start_time, philo->id);
	pthread_mutex_lock(&(philo->right_fork));
	printf(YEL "%lld %d has taken a fork\n" RESET, philo->data->current_time
		- philo->data->start_time, philo->id);
	philo->status = EATING;
	philo->last_meal_time = philo->data->current_time;
	printf(GRN "%lld %d is eating\n" RESET, philo->data->current_time
		- philo->data->start_time, philo->id);
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
}

void	monitor(t_data *data)
{
	long long	now;
	int			i;
	int			time_passed;

	i = 0;
	while (i < data->n_phil)
	{
		now = get_current_time();
		data->current_time = now;
		time_passed = now - data->philos[i].last_meal_time;
		if (time_passed > data->time_to_die && data->philos->status != EATING)
		{
			printf(RED "%d %d died\n" RESET, time_passed, data->philos[i].id);
			data->philos[i].status = DEAD;
			data->finish = true;
			break ;
		}
		if (data->philos[i].meals_eaten == data->n_meals
			&& data->philos[i].checked == false)
		{
			data->nr_full++;
			data->philos[i].checked = true;
		}
		i++;
	}
	if (data->nr_full == data->n_phil)
		data->finish = true;
}
