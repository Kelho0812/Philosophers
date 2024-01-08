/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:06:06 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/08 10:53:16 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		error_handler(WRONG_ARG, NULL, NULL);
	initializer(&data, argv);
	threads_create(&data);
	while (data.finish != true)
		monitor(&data);
	threads_join(&data);
	ft_exit(&data);
	return (0);
}
