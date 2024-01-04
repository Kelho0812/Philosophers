/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:44:45 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 18:11:54 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long	get_current_time(void)
{
	struct timeval	tv;
	long long		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (long long)(tv.tv_sec)*1000 + (long long)(tv.tv_usec)
		/ 1000;
	return (milliseconds);
}

int	ft_usleep(unsigned long long time)
{
	unsigned long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < time)
		usleep(time / 10);
	return (0);
}
