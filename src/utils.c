/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:13:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/04 17:56:10 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	ft_atoi_change(const char *str);
int		ft_isdigit(int n);

void	arg_checker_parser(t_data *data, char **argv)
{
	num_checker(argv);
	data->n_phil = ft_atoi_change(argv[1]);
	data->time_to_die = ft_atoi_change(argv[2]);
	data->time_to_eat = ft_atoi_change(argv[3]);
	data->time_to_sleep = ft_atoi_change(argv[4]);
	if (argv[5])
		data->n_meals = ft_atoi_change(argv[5]);
	else
		data->n_meals = 0;
	if (data->n_phil <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		error_handler(INVALID_TIME, NULL, NULL);
}

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

void	num_checker(char **argv)
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
			{
				error_handler(WRONG_CHARS, NULL, NULL);
			}
			n++;
		}
		i++;
	}
}

int	ft_isdigit(int n)
{
	if (n >= 48 && n <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
