/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorteixe  <jorteixe@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:35:40 by jorteixe          #+#    #+#             */
/*   Updated: 2024/01/11 11:16:12 by jorteixe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers_bonus.h"

void	dinner(t_data *data)
{
	if (data->meals_to_eat == 0)
		return ;
	else if (data->nbr_philos == 1) // TODO
		;
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
	long long	time_passed;

	sem_unlink(SEM_PHILO);
	philos->philo_sem = sem_open(SEM_PHILO, O_CREAT, 0600, 1);
	philos->forks_sem = sem_open(SEM_FORKS, 0);
	philos->dead_sem = sem_open(SEM_DEAD, 0);
	set_long_long(philos->philo_sem, &philos->last_meal_time,
		get_current_time());
	set_long_long(philos->philo_sem, &philos->start_time,
		get_current_time());
	pthread_create(&(philos->philo_thread), NULL, &routine,
		(philos));
	while (!get_bool(philos->philo_sem, &philos->is_full)
		&& !get_bool(philos->philo_sem, &philos->is_dead))
	{
		time_passed = get_current_time()
			- get_long_long(philos->philo_sem,
				&philos->last_meal_time);
		if (time_passed > philos->data->time_to_die)
		{
			set_bool(philos->philo_sem, &philos->is_dead, true);
			write_action(DEAD, philos);
		}
	}
	pthread_join(philos->philo_thread, NULL);
	sem_close(philos->philo_sem);
	return ;
}
void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!get_bool(philo->philo_sem, &philo->is_dead))
	{
		write_action(THINKING, philo);
		ft_usleep(1);
		if (philo->is_full)
			return (NULL);
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	sem_wait(philo->forks_sem);
	write_action(TAKE_FIRST_FORK, philo);
	write_action(TAKE_SECOND_FORK, philo);
	set_long_long(philo->philo_sem, &philo->last_meal_time, get_current_time());
	write_action(EATING, philo);
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

void	write_action(t_status status, t_philo *philo)
{
	long long	time_passed;

	time_passed = get_current_time() - get_long_long(philo->philo_sem,
			&philo->start_time);
	sem_wait(philo->dead_sem);
	if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		printf(WHT "%lld" YEL " %d has taken a fork\n" RESET, time_passed,
			philo->id);
	else if (status == SLEEPING)
		printf(WHT "%lld" RESET " %d is sleeping\n", time_passed, philo->id);
	else if (status == THINKING)
		printf(WHT "%lld" RESET " %d is thinking\n", time_passed, philo->id);
	else if (status == EATING)
		printf(WHT "%lld" CYN " %d is eating\n" RESET, time_passed, philo->id);
	sem_post(philo->dead_sem);
	if (status == DEAD)
	{
		sem_wait(philo->dead_sem);
		printf(RED "%lld %d died\n" RESET, time_passed, philo->id);
	}
}
