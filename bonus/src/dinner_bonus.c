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
	else if (data->nbr_philos == 1)
		;
	else
		processes_create(data);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_long_long(&philo->philo_mutex, &philo->last_meal_time,
		get_current_time());
	increase_threads_running_nbr(&philo->data->data_mutex,
		&philo->data->nbr_threads_running);
	while (!dinner_finished(philo->data))
	{
		// if (philo->full)
		// 	break ;
		write_action(THINKING, philo);
		ft_usleep(1);
		eating(philo);
		write_action(SLEEPING, philo);
		ft_usleep(philo->data->time_to_sleep);
	}
	return (NULL);
}

void	processes_create(t_data *data)
{
	int		i;
	sem_t	*forks;
	sem_t	*dead;

	// criar sem forks
	forks = sem_unlink(SEM_FORKS);
	dead = sem_unlink(SEM_DEAD);
	sem_open(SEM_DEAD, O_CREAT, 0600, 1);
	sem_open(SEM_FORKS, O_CREAT, 0600, 1);
	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			threads_create(data);
			return ;
		}
		i++;
	}
	sem_close(SEM_FORKS);
	sem_close(SEM_DEAD);
}

void	threads_create(t_data *data)
{
	sem_t	*philo_sem;

	sem_unlink(SEM_PHILO);
	philo_sem = sem_open(SEM_PHILO, O_CREAT, 0600, 0);
	data->philos->forks_sem = sem_open(SEM_FORKS, 0);
	data->philos->dead_sem = sem_open(SEM_DEAD, 0);
	pthread_create(&(data->philos->philo_thr), NULL, &routine, &(data->philos));
	sem_close(philo_sem);
	sem_unlink(philo_sem);
}

void	eating(t_philo *philo)
{
	// if (get_bool(&philo->philo_mutex, &philo->full))
	// 	return ;
	pthread_mutex_lock(&philo->first_fork->fork);
	write_action(TAKE_FIRST_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	write_action(TAKE_SECOND_FORK, philo);
	set_long_long(&philo->philo_mutex, &philo->last_meal_time,
		get_current_time());
	write_action(EATING, philo);
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	if (philo->data->meals_to_eat > 0
		&& philo->meals_eaten == philo->data->meals_to_eat)
	{
		set_bool(&philo->philo_mutex, &philo->full, true);
	}
	pthread_mutex_unlock(&philo->second_fork->fork);
	pthread_mutex_unlock(&philo->first_fork->fork);
}

void	write_action(t_status status, t_philo *philo)
{
	long long	time_passed;

	time_passed = get_current_time - philo->start_time;
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
