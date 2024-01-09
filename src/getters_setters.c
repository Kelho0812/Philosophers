/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:00:10 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 16:40:19 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	set_bool(t_mtx *mutex, bool *bool_pointer, bool value)
{
	pthread_mutex_lock(mutex);
	*bool_pointer = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(t_mtx *mutex, bool *bool_pointer)
{
	bool	local_bool;

	pthread_mutex_lock(mutex);
	local_bool = *bool_pointer;
	pthread_mutex_unlock(mutex);
	return (local_bool);
}

void	set_long_long(t_mtx *mutex, long long *llpointer, long long value)
{
	pthread_mutex_lock(mutex);
	*llpointer = value;
	pthread_mutex_unlock(mutex);
}

long long	get_long_long(t_mtx *mutex, long long *llpointer)
{
	long long	local_ll;

	pthread_mutex_lock(mutex);
	local_ll = *llpointer;
	pthread_mutex_unlock(mutex);
	return (local_ll);
}

bool	dinner_finished(t_data *data)
{
	return (get_bool(&data->data_mutex, &data->finish));
}