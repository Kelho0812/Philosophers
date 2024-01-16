/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:28:14 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 10:31:54 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!initializer(&data, argv, argc))
			return (1);
		dinner(&data);
		ft_exit(&data);
	}
	else
		return (error_handler(WRONG_ARG_NR));
	return (0);
}
