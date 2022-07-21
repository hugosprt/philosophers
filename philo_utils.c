#include "philo.h"

void	take_forks(t_philo *philo, uint64_t timestamp)
{
	pthread_mutex_lock(&philo->data->miammiam[philo->l_fork]);
	print_tfk(philo, TOOK_FORK, timestamp);
	pthread_mutex_lock(&philo->data->death);
	if (!philo->data->no_one_died)
	{
		
	}
	pthread_mutex_unlock(&philo->data->death);
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
	pthread_mutex_lock(&philo->data->eating);
	philo->last_eat = timestamp;
	pthread_mutex_unlock(&philo->data->eating);
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
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->no_one_died)
	{
		printf("%lu %d %s\n", timestamp, philo->id, states[tfk]);
		
	}
	pthread_mutex_unlock(&philo->data->death);
}