#include "philo.h"

void	take_forks(t_philo *philo, uint64_t timestamp)
{
	pthread_mutex_lock(&philo->data->miammiam[philo->l_fork]);
	print_tfk(philo, TOOK_FORK, timestamp);
	pthread_mutex_lock(&philo->data->miammiam[philo->r_fork]);
	print_tfk(philo, TOOK_FORK, timestamp);
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->miammiam[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->miammiam[philo->r_fork]);
}

void	philo_eat(t_philo *philo, uint64_t timestamp)
{
	print_tfk(philo, EATING, timestamp);
	philo->eat++;
	philo->last_eat = timestamp;
	usleep(philo->data->teat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	print_tfk(philo, SLEEPING, get_time());
	usleep(philo->data->tsleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_tfk(philo, THINKING, get_time());
}

void	print_tfk(t_philo *philo, t_tfk tfk, uint64_t timestamp)
{
	const char	*states[6] = {"is thinking", "is eating", "is sleeping",
		"has taken a fork", "died", NULL};

	printf("%llu %d %s\n", timestamp, philo->id, states[tfk]);
}