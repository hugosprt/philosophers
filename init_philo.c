#include "philo.h"

void	finish(t_data *data)
{
	int	i;

	i = 0;
    //(void) i;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->miammiam[i]);
		i++;
	}
	pthread_mutex_destroy(&data->eating);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->finish);
	free(data->philo);
	i = 0;
	free(data->tid);
	free(data->miammiam);
	//pthread_mutex_destroy(&data->miammiam);
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void *routine(void *arg) 
{
    t_philo *filo;

    filo = (t_philo *) arg;
	pthread_mutex_lock(&filo->data->eating);
	filo->last_eat = get_time();
	pthread_mutex_unlock(&filo->data->eating);
	if (filo->id % 2 != 0)
	{
		philo_think(filo);
		usleep((filo->data->teat) * 0.25 * 1000);
	}
	pthread_mutex_lock(&filo->data->death);
	while (filo->data->no_one_died)
	{
		pthread_mutex_unlock(&filo->data->death);
		//take_forks(filo, get_time());
		pthread_mutex_lock(&filo->data->miammiam[filo->l_fork]);
		print_tfk(filo, TOOK_FORK, get_time());
		pthread_mutex_lock(&filo->data->death);
		if (filo->l_fork == filo->r_fork)
		{
			pthread_mutex_unlock(&filo->data->miammiam[filo->l_fork]);
			break ;
		}
		pthread_mutex_unlock(&filo->data->death);
		pthread_mutex_lock(&filo->data->miammiam[filo->r_fork]);
		print_tfk(filo, TOOK_FORK, get_time());
		philo_eat(filo, get_time());
		leave_forks(filo);
		philo_think(filo);
		if (filo->eat == filo->data->num_eat)
		{
			pthread_mutex_lock(&filo->data->finish);
			filo->is_finish = 1;
			filo->data->as_finish++;
			pthread_mutex_unlock(&filo->data->finish);
			pthread_mutex_lock(&filo->data->death);
			break ;
		}
		philo_sleep(filo);
		pthread_mutex_lock(&filo->data->death);
	}
	pthread_mutex_unlock(&filo->data->death);
	pthread_exit(NULL);
}

void    init_philo(t_data *data)
{
    int i;

    i= 0;
    data->philo = malloc(sizeof(t_philo) * (data->num_philosophers));
    data->tid = malloc(sizeof(pthread_t) * data->num_philosophers);
    data->miammiam = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	pthread_mutex_init(&data->finish, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->eating, NULL);
    while   (i < data->num_philosophers)
    {
        data->philo[i].num_eat = data->num_eat;
        memset(&data->philo[i], 0, sizeof(t_philo));
        memset(&data->tid[i], 0, sizeof(pthread_t));
    //    memset(&data->miammiam[i], 0, sizeof(pthread_mutex_t));
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
		{
			pthread_mutex_unlock(&data->finish);
			break ;
		}
		pthread_mutex_unlock(&data->finish);
		if (index == data->num_philosophers)
			index = 0;
		usleep(1000);
		timestamp = get_time();
		pthread_mutex_lock(&data->eating);
		pthread_mutex_lock(&data->finish);
		if (!data->philo[index].is_finish && (int)(timestamp - data->philo[index].last_eat) > data->tdie)
		{
			print_tfk(&data->philo[index], DEAD, get_time());
			pthread_mutex_lock(&data->death);
			data->no_one_died = 0;
			pthread_mutex_unlock(&data->death);
			break ;
		}
		pthread_mutex_unlock(&data->finish);
		pthread_mutex_unlock(&data->eating);

		index++;
	}
	return (NULL);
}

void number_philo(t_data *data) 
{
    int i;
    pthread_t rourou;

    i = 0;
    init_philo(data);
	while (i <  data->num_philosophers) 
    {
        data->philo[i].eat = 0;
		pthread_create(&data->tid[i], NULL, routine, (void*)&data->philo[i]);
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
