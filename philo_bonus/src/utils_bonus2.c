/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 17:14:16 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	write_action(t_status status, t_philo *philo)
{
	long long	time_passed;

	time_passed = get_current_time() - get_long_long(philo->philo_sem,
			&philo->start_time);
	if (!get_bool(philo->philo_sem, &philo->is_dead))
	{
		sem_wait(philo->dead_sem);
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
		sem_post(philo->dead_sem);
	}
}
