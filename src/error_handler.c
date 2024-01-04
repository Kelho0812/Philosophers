/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:06:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 18:13:16 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_handler(int error, void *param, void **param2)
{
	(void)param;
	(void)param2;
	if (error == WRONG_ARG)
	{
		printf(RED "Wrong num of Arguments\n" RESET);
		printf("Please write: " CYN "./philo " RESET);
		printf(GRN "<number_of_philosophers> <time_to_die>");
		printf("<time_to_eat> <time_to_sleep> ");
		printf("[number_of_times_each_philosopher_must_eat](optional)\n" RESET);
	}
	if (error == WRONG_CHARS)
	{
		printf("Arguments must be " RED "only " GRN "numbers\n" RESET);
	}
	if (error == INVALID_TIME)
	{
		printf("Arguments " RED "can't be " RESET "negative or 0\n");
	}
	exit(1);
}
