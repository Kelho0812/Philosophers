/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:13:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 16:28:40 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	ft_atoi_change(const char *str)
{
	unsigned char	*s;
	int				i;
	long			n;

	s = (unsigned char *)str;
	i = 0;
	n = 0;
	while (s[i] >= '0' && s[i] <= '9' && s[i] != '\0')
	{
		n = n * 10;
		n = n + (s[i] - '0');
		i++;
	}
	return (n);
}

int	num_checker(char **argv)
{
	int	i;
	int	n;

	i = 1;
	while (argv[i] != NULL)
	{
		n = 0;
		while (argv[i][n] != '\0')
		{
			if (ft_isdigit(argv[i][n]) == 0)
				return (error_handler(WRONG_CHARS));
			n++;
		}
		i++;
	}
	return (1);
}

int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
		return (1);
	else
		return (0);
}
