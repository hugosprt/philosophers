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

void * routine(void *arg) 
{   

    t_philo *filo;

    filo = (t_philo *) arg;

    
	//Vérouillage du mutex
	if (filo->id % 2 == 0)
	{
		usleep(filo->data->tsleep);
	}
	while (1 && filo->eat < filo->data->num_eat)
	{
		if (filo->id < filo->data->num_philosophers)
		{
			pthread_mutex_lock(&(filo->data->miammiam[filo->id - 1]));
			pthread_mutex_lock(&(filo->data->miammiam[filo->id]));
			filo->eat++;
			printf("philo [%d ] a mange [ %i ] fois \n",filo->id,filo->eat);
			usleep(filo->data->teat);
			pthread_mutex_unlock(&(filo->data->miammiam[filo->id]));
			pthread_mutex_unlock(&(filo->data->miammiam[filo->id - 1]));
		}
		else
		{
			pthread_mutex_lock(&(filo->data->miammiam[filo->id - 1]));
			pthread_mutex_lock(&(filo->data->miammiam[0]));
			filo->eat++;
			printf("philo [%d ] a mange [ %i ] fois \n",filo->id,filo->eat);
			usleep(filo->data->teat);
			pthread_mutex_unlock(&(filo->data->miammiam[0]));
			pthread_mutex_unlock(&(filo->data->miammiam[filo->id -1]));
			
		}
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
        data->philo[i].id = i + 1;
        i++;
    }
}

void number_philo(t_data *data) 
{
    int i;
    int err;

    i = 0;
    init_philo(data);
	while (i <  data->num_philosophers) 
    {
        data->philo[i].eat = 0;
		// Création du thread et passage de la structure par référence
		err = pthread_create(&data->tid[i], NULL, routine, (void*)&data->philo[i]);
		if (err != 0) {
			printf("Echec de la création du thread: [%s]", strerror(err));
			break;
		}
		printf("Création du thread numéro %d\n", (int)data->tid[i]);
        i++;
	}
	// En attente des threads
	for (int i = 0; i <  data->num_philosophers; i++) {
		pthread_join(data->tid[i], NULL);
	}
	// Destruction du mutex

}
