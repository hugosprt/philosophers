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

void    *ft_routine(void * arg)
{
    (void) arg;
    data->philo.is_alive = 0;
   return (NULL);
}

void    number_philo(t_data *data)
{
    int i;
   

    data->philo = malloc(sizeof(t_philo) * (data->num_philosophers));
    if (data->philo == NULL)
        return ;
    i = 0;  
    while (i < data->num_philosophers)
    {
        pthread_create(&(data->philo[i].tid) , NULL, &ft_routine, NULL);
        data->philo[i].id = i + 1;
        data->philo[i].num_eat = data->num_eat;
        data->philo[i].is_alive = 1;
        i++;
    }
    i = 0; 
    while (i < data->num_philosophers)
    {
        printf("philo %d :", data->philo[i].id);
        printf(" num eat %d,", data->philo[i].num_eat);  
        printf(" is alive %d. ", data->philo[i].is_alive);
        printf("\n");
        i++;
    }
}
