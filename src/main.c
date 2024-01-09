/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 10:06:06 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 16:32:07 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 5 && argc == 6)
	{
		if (!initializer(&data, argv, argc))
			return(1);
		dinner(&data);
		ft_exit(&data);
	}
	else
		return(error_handler(WRONG_ARG_NR));
	return (0);	
}
