/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:20:56 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 11:29:06 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*routine_one(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	printf(YEL "%d %d has taken a fork\n" RESET, 0, 1);
	ft_usleep(philo->data->time_to_die);
	printf(RED "%d %d died\n" RESET, philo->data->time_to_die, 1);
	return (NULL);
}

void	write_action(t_status status, t_philo *philo)
{
	long long	time_passed;

	time_passed = get_current_time() - get_long_long(&philo->data->data_mutex,
			&philo->data->start_time);
	pthread_mutex_lock(&philo->data->write_mutex);
	if (!dinner_finished(philo->data))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf(WHT "%lld" YEL " %d has taken a fork\n" RESET, time_passed,
				philo->id);
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
