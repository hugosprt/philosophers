/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:21:02 by hspriet           #+#    #+#             */
/*   Updated: 2022/07/23 14:32:04 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	leave_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_unlock(&philo->data->miammiam[philo->l_fork]);
		pthread_mutex_unlock(&philo->data->miammiam[philo->r_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->miammiam[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->miammiam[philo->l_fork]);
	}
}

void	philo_eat(t_philo *philo, uint64_t timestamp)
{
	print_tfk(philo, EATING, timestamp);
	philo->eat++;
	pthread_mutex_lock(&philo->data->eating);
	philo->last_eat = timestamp;
	pthread_mutex_unlock(&philo->data->eating);
	ft_usleep(philo->data->teat);
}

void	philo_sleep(t_philo *philo)
{
	print_tfk(philo, SLEEPING, get_time());
	ft_usleep(philo->data->tsleep);
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
		printf("%lu %d %s\n", (timestamp - philo->data->starting_time),
			philo->id, states[tfk]);
	}
	pthread_mutex_unlock(&philo->data->death);
}
