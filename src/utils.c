/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 09:30:48 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/09 21:37:09 by jorteixe         ###   ########.fr       */
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

long long	get_current_time(void)
{
	struct timeval	tv;
	long long		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = (long long)(tv.tv_sec) *1000 + (long long)(tv.tv_usec)
		/ 1000;
	return (milliseconds);
}

int	ft_usleep(long long milliseconds)
{
	long long	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
