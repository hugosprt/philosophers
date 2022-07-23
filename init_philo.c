/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 14:20:51 by hspriet           #+#    #+#             */
/*   Updated: 2022/07/23 18:54:37 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_finish(t_philo *filo)
{
	pthread_mutex_lock(&filo->data->finish);
	filo->is_finish = 1;
	filo->data->as_finish++;
	pthread_mutex_unlock(&filo->data->finish);
}

void	*routine(void *arg)
{
	t_philo	*filo;

	filo = (t_philo *) arg;
	pthread_mutex_lock(&filo->data->eating);
	filo->last_eat = get_time();
	pthread_mutex_unlock(&filo->data->eating);
	pthread_mutex_lock(&filo->data->death);
	pthread_mutex_lock(&filo->data->finish);
	while (filo->data->no_one_died && filo->data->as_finish
		!= filo->data->num_philosophers)
	{
		pthread_mutex_unlock(&filo->data->finish);
		pthread_mutex_unlock(&filo->data->death);
		if (take_forks(filo))
			break ;
		philo_eat(filo, get_time());
		leave_forks(filo);
		philo_sleep(filo);
		if (filo->eat == filo->data->num_eat)
			philo_finish(filo);
		philo_think(filo);
		pthread_mutex_lock(&filo->data->death);
		pthread_mutex_lock(&filo->data->finish);
	}
	pthread_mutex_unlock(&filo->data->finish);
	pthread_mutex_unlock(&filo->data->death);
	return (NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->num_philosophers));
	data->tid = malloc(sizeof(pthread_t) * data->num_philosophers);
	data->miammiam = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	pthread_mutex_init(&data->finish, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->eating, NULL);
	pthread_mutex_init(&data->write, NULL);
	while (i < data->num_philosophers)
	{
		data->philo[i].num_eat = data->num_eat;
		memset(&data->philo[i], 0, sizeof(t_philo));
		memset(&data->tid[i], 0, sizeof(pthread_t));
		data->philo[i].data = data;
		data->philo[i].is_finish = 0;
		data->philo[i].id = i + 1;
		data->no_one_died = 1;
		data->philo[i].last_eat = 0;
		data->philo[i].l_fork = i;
		data->philo[i].r_fork = (i + 1) % data->num_philosophers;
		pthread_mutex_init(&data->miammiam[i], NULL);
		i++;
	}
}

void	*routine2(void *arg)
{
	int			index;
	uint64_t	timestamp;
	t_data		*data;

	data = (t_data *)arg;
	index = 0;
	while (1)
	{
		pthread_mutex_lock(&data->finish);
		if (data->as_finish == data->num_philosophers)
			break ;
		pthread_mutex_unlock(&data->finish);
		index = normi(data, index);
		ft_usleep(1);
		timestamp = get_time();
		ft_zz(data);
		if (!data->philo[index].is_finish && (int)
			(timestamp - data->philo[index].last_eat) > data->tdie)
		{
			index = ft_25ligne(data, index);
			break ;
		}
		ft_zzz(data);
	}
	return (pthread_mutex_unlock(&data->finish), NULL);
}

void	number_philo(t_data *data)
{
	int			i;
	pthread_t	rourou;

	i = 0;
	init_philo(data);
	data->starting_time = get_time();
	while (i < data->num_philosophers)
	{
		data->philo[i].eat = 0;
		pthread_create(&data->tid[i], NULL, routine, (void *) &data->philo[i]);
		i++;
	}
	i = 0;
	pthread_create(&rourou, NULL, routine2, data);
	pthread_join(rourou, NULL);
	while (i < data->num_philosophers)
	{
		pthread_join(data->tid[i], NULL);
		i++;
	}
}
