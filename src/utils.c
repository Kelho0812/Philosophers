/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:13:03 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/08 16:10:20 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	initializer(t_data *data, char **argv)
{
	num_checker(argv);
	data->n_phil = ft_atoi_change(argv[1]);
	data->time_to_die = ft_atoi_change(argv[2]);
	data->time_to_eat = ft_atoi_change(argv[3]);
	data->time_to_sleep = ft_atoi_change(argv[4]);
	data->start_time = get_current_time();
	data->current_time = get_current_time();
	data->finish = false;
	data->nr_full = 0;
	if (argv[5])
	{
		data->n_meals = ft_atoi_change(argv[5]);
		if (data->n_meals < 0)
			error_handler(INVALID_TIME, NULL, NULL);
	}
	else
		data->n_meals = -1;
	if (data->n_phil <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		error_handler(INVALID_TIME, NULL, NULL);
	initialize_philos(data);
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

void	monitor(t_data *data)
{
	long long	now;
	int			i;
	int			time_passed;

	i = 0;
	while (i < data->n_phil)
	{
		now = get_current_time();
		data->current_time = now;
		time_passed = now - data->philos[i].last_meal_time;
		if (time_passed > data->time_to_die && data->philos->status != EATING)
		{
			printf(RED "%d %d died\n" RESET, time_passed, data->philos[i].id);
			data->philos[i].status = DEAD;
			data->finish = true;
			break ;
		}
		if (data->philos[i].meals_eaten == data->n_meals && data->philos[i].checked == false)
		{
			// printf("Full Phil ID: %d\n", data->philos[i].id);
			data->nr_full++;
			data->philos[i].checked = true;
		}
		i++;
	}
	if (data->nr_full == data->n_phil)
	{
		data->finish = true;
	}
}
