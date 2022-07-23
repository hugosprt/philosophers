/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:34:07 by hspriet           #+#    #+#             */
/*   Updated: 2022/07/23 15:35:25 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_zz(t_data *data)
{
	pthread_mutex_lock(&data->eating);
	pthread_mutex_lock(&data->finish);
}

void	ft_zzz(t_data *data)
{
	pthread_mutex_unlock(&data->finish);
	pthread_mutex_unlock(&data->eating);
}
