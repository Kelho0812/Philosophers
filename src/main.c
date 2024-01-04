/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:06:06 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 10:58:36 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 5 || argc != 6)
		error_handler(WRONG_ARG, NULL, NULL);
	long long now;
	long long after;
	now = get_current_time();
	printf("Current time in milliseconds: %lld\n", now);
	usleep(300000);
	after = get_current_time();
    printf("After time in milliseconds: %lld\n", after);
	printf("Difference time in milliseconds: %lld\n", (after-now));

}
