#include "../include/philosophers_bonus.h"

void	write_action(t_status status, t_philo *philo)
{
	long long	time_passed;

	time_passed = get_current_time() - get_long_long(philo->philo_sem,
			&philo->start_time);
	if (!get_bool(philo->philo_sem, &philo->is_dead))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		{
			sem_wait(philo->dead_sem);
			printf(WHT "%lld" YEL " %d has taken a fork\n" RESET, time_passed,
				philo->id);
			sem_post(philo->dead_sem);
		}
		else if (status == SLEEPING)
		{
			sem_wait(philo->dead_sem);
			printf(WHT "%lld" RESET " %d is sleeping\n", time_passed,
				philo->id);
			sem_post(philo->dead_sem);
		}
		else if (status == THINKING)
		{
			sem_wait(philo->dead_sem);
			printf(WHT "%lld" RESET " %d is thinking\n", time_passed,
				philo->id);
			sem_post(philo->dead_sem);
		}
		else if (status == EATING)
		{
			sem_wait(philo->dead_sem);
			printf(WHT "%lld" CYN " %d is eating\n" RESET, time_passed,
				philo->id);
			sem_post(philo->dead_sem);
		}
	}
}