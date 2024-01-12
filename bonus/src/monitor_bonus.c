// /* ************************************************************************** */
// `/*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   monitor_bonus.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
// /*   Updated: 2024/01/11 11:16:12 by jorteixe         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// # include "../include/philosophers_bonus.h"


// static bool	check_dead(t_philo *philo);

// void	*monitor(void *table)
// {
// 	int			i;
// 	t_data		*data;
// 	long long	time_passed;

// 	data = (t_data *)table;
// 	while (!all_threads_running(&data->data_mutex, &data->nbr_threads_running,
// 			data->nbr_philos))
// 		;
// 	while (!dinner_finished(data))
// 	{
// 		i = 0;
// 		data->full_count = 0;
// 		while (i < data->nbr_philos && !dinner_finished(data))
// 		{
// 			if (check_dead(&data->philos[i]))
// 			{
// 				time_passed = get_current_time()
// 					- get_long_long(&data->data_mutex, &data->start_time);
// 				set_bool(&data->data_mutex, &data->finish, true);
// 				printf(RED "%lld %d died\n" RESET, time_passed,
// 					data->philos->id);
// 			}
// 			if (get_bool(&data->philos[i].philo_mutex, &data->philos[i].is_full))
// 				data->full_count++;
// 			i++;
// 		}
// 		if (data->full_count == data->nbr_philos)
// 			set_bool(&data->data_mutex, &data->finish, true);
// 	}
// 	return (NULL);
// }


// static bool	check_dead(t_philo *philo)
// {
// 	long long time_passed;
// 	long long time_to_die;

// 	if (get_bool(&philo->philo_mutex, &philo->is_full))
// 		return (false);

// 	time_to_die = philo->data->time_to_die;
// 	time_passed = get_current_time() - get_long_long(&philo->philo_mutex,
// 			&philo->last_meal_time);
// 	if (time_passed >= time_to_die)
// 		return (true);
// 	return (false);
// }