/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe <jorteixe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/16 12:50:03 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	dinner(t_data *data)
{
	if (data->meals_to_eat == 0)
		return ;
	else if (data->nbr_philos == 1)
	{
		data->philos->pid = fork();
		if (data->philos->pid == -1)
			error_handler(WRONG_PID);
		if (data->philos->pid == 0)
		{
			printf(YEL "%d %d has taken a fork\n" RESET, 0, 1);
			ft_usleep(data->time_to_die);
			printf(RED "%d %d died\n" RESET, data->time_to_die, 1);
			return ;
		}
	}
	else
		processes_create(data);
}

void	processes_create(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
			error_handler(WRONG_PID);
		if (data->philos[i].pid == 0)
		{
			threads_create(&data->philos[i]);
			return ;
		}
		i++;
	}
	while (1)
	{
		if (waitpid(-1, NULL, WNOHANG) != 0)
		{
			i = 0;
			while (i < data->nbr_philos - 1)
				kill(data->philos[i++].pid, SIGINT);
			return ;
		}
	}
}

void	threads_create(t_philo *philos)
{
	sem_unlink(SEM_PHILO);
	philos->philo_sem = sem_open(SEM_PHILO, O_CREAT, 0600, 1);
	philos->forks_sem = sem_open(SEM_FORKS, 0);
	philos->dead_sem = sem_open(SEM_DEAD, 0);
	philos->last_meal_time = get_current_time();
	philos->start_time = get_current_time();
	pthread_create(&(philos->philo_thread), NULL, &routine, philos);
	while (!get_bool(philos->philo_sem, &philos->is_full)
		&& !get_bool(philos->philo_sem, &philos->is_dead))
	{
		monitor(philos);
	}
	pthread_join(philos->philo_thread, NULL);
	sem_close(philos->philo_sem);
	sem_close(philos->forks_sem);
	sem_close(philos->dead_sem);
	return ;
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long_long(philo->philo_sem, &philo->last_meal_time, get_current_time());
	while (!get_bool(philo->philo_sem, &philo->is_dead) && !get_bool(philo->philo_sem, &philo->is_full))
	{
		write_action(THINKING, philo);
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	if (get_bool(philo->philo_sem, &philo->is_dead))
		return ;
	sem_wait(philo->forks_sem);
	sem_wait(philo->forks_sem);
	write_action(TAKE_FIRST_FORK, philo);
	write_action(TAKE_SECOND_FORK, philo);
	write_action(EATING, philo);
	set_long_long(philo->philo_sem, &philo->last_meal_time, get_current_time());
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	if (philo->data->meals_to_eat > 0
		&& philo->meals_eaten == philo->data->meals_to_eat)
	{
		set_bool(philo->philo_sem, &philo->is_full, true);
	}
	sem_post(philo->forks_sem);
	sem_post(philo->forks_sem);
}
