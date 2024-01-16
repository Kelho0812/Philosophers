/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:51:29 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 11:59:44 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 || argc == 6)
	{
		if (!initializer(&data, argc, argv))
			return (1);
		dinner(&data);
		ft_exit(&data);
	}
	else
		return (error_handler(WRONG_ARG_NR));
	return (0);
}
