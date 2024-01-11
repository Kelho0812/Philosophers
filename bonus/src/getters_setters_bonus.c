/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/11 11:16:12 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	set_bool(sem_t *sem, bool *bool_pointer, bool value)
{
	sem_wait(sem);
	*bool_pointer = value;
	sem_post(sem);
}

bool	get_bool(sem_t *sem, bool *bool_pointer)
{
	bool	local_bool;

	sem_wait(sem);
	local_bool = *bool_pointer;
	sem_post(sem);
	return (local_bool);
}

void	set_long_long(sem_t *sem, long long *llpointer, long long value)
{
	sem_wait(sem);
	*llpointer = value;
	sem_post(sem);
}

long long	get_long_long(sem_t *sem, long long *llpointer)
{
	long long	local_ll;

	sem_wait(sem);
	local_ll = *llpointer;
	sem_post(sem);
	return (local_ll);
}
