/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:20:59 by hspriet           #+#    #+#             */
/*   Updated: 2022/07/23 15:59:21 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t	time)
{
	const size_t	instant_t = get_time();

	while (get_time() - instant_t < time)
	{
		usleep(500);
	}
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	take_forks(t_philo *philo)
{
	if (philo->data->num_philosophers == 1)
	{
		print_tfk(philo, TOOK_FORK, get_time());
		ft_usleep(philo->data->tdie);
		print_tfk(philo, DEAD, get_time());
		pthread_mutex_lock(&philo->data->death);
		philo->data->no_one_died = 0;
		return (1);
	}
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->data->miammiam[philo->r_fork]);
		print_tfk(philo, TOOK_FORK, get_time());
		pthread_mutex_lock(&philo->data->miammiam[philo->l_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->miammiam[philo->l_fork]);
		print_tfk(philo, TOOK_FORK, get_time());
		pthread_mutex_lock(&philo->data->miammiam[philo->r_fork]);
	}
	print_tfk(philo, TOOK_FORK, get_time());
	return (0);
}

void	finish(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->miammiam[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->finish);
	pthread_mutex_destroy(&data->write);
	free(data->philo);
	i = 0;
	free(data->tid);
	free(data->miammiam);
}

int	ft_25ligne(t_data *data, int index)
{
	print_tfk(&data->philo[index], DEAD, get_time());
	pthread_mutex_lock(&data->death);
	data->no_one_died = 0;
	pthread_mutex_unlock(&data->death);
	pthread_mutex_unlock(&data->eating);
	return (index + 1);
}
