#include "philo.h"

void	finish(t_data *data)
{
	int	i;

	i = 0;
    (void) i;
	// while (data->philo[i] != NULL)
	// {
	// 	free(data->philo[i]);
	// 	i++;
	// }
	free(data->philo);
	i = 0;
	free(data);
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void * routine(void *arg) 
{   

    t_philo *filo;

    filo = (t_philo *) arg;
	filo->last_eat = get_time();
	if (filo->id % 2 == 0)
	{
		philo_think(filo);
		usleep(filo->data->teat * 0.25 * 1000);
	}
	while (filo->data->no_one_died)
	{
		take_forks(filo, get_time());
		philo_eat(filo, get_time());
		leave_forks(filo);
		philo_think(filo);
		if (filo->eat == filo->data->num_eat)
		{
			filo->is_finish = 1;
			filo->data->as_finish++;
			break ;
		}
		philo_sleep(filo);
	}
	pthread_exit(NULL);
}

void    init_philo(t_data *data)
{
    int i;

    i= 0;
    data->philo = malloc(sizeof(t_philo) * (data->num_philosophers));
    data->tid = malloc(sizeof(pthread_t) * data->num_philosophers);
    data->miammiam = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
    while   (i < data->num_philosophers)
    {
        data->philo[i].num_eat = data->num_eat;
        memset(&data->philo[i], 0, sizeof(t_philo));
        memset(&data->tid[i], 0, sizeof(pthread_t));
        memset(&data->miammiam[i], 0, sizeof(pthread_mutex_t));
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
		if (data->as_finish == data->num_philosophers)
			break ;
		if (index == data->num_philosophers)
			index = 0;
		usleep(1000);
		timestamp = get_time();
		if (!data->philo[index].is_finish && (int)(timestamp - data->philo[index].last_eat) > data->tdie)
		{
			print_tfk(&data->philo[index], DEAD, get_time());
			data->no_one_died = 0;
			break ;
		}
		index++;
	}
	return (NULL);
}

void number_philo(t_data *data) 
{
    int i;
    pthread_t rourou;

    i = 0;
	 //(void) rourou;
    init_philo(data);
	while (i <  data->num_philosophers) 
    {
        data->philo[i].eat = 0;
		pthread_create(&data->tid[i], NULL, routine, (void*)&data->philo[i]);
		//printf("Création du thread numéro %d\n", (int)data->tid[i]);
        i++;
	}
	pthread_create(&rourou, NULL, routine2, data);
	pthread_join(rourou, NULL);
}
