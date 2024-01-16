/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:20:56 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 11:21:51 by jorteixe         ###   ########.fr       */
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
