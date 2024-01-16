/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:56:47 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 12:34:30 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	monitor(void *data)
{
	long long	time_passed;
	t_philo		*philos;

	philos = (t_philo *)data;
	
	time_passed = get_current_time() - get_long_long(philos->philo_sem,
			&philos->last_meal_time);
	if (time_passed > philos->data->time_to_die)
	{
		sem_wait(philos->dead_sem);
		set_bool(philos->philo_sem, &philos->is_dead, true);
		printf(RED"%lld %d died\n"RESET, time_passed, philos->id);
		// write_action(DEAD, philos);
		return ;
	}
}
