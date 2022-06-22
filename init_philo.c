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
   // data->philo.is_alive = 0;
   return (NULL);
}

void    number_philo(t_data *data)
{
    int i;
    t_philo *philosofe;

    philosofe = malloc(sizeof(t_philo) * (data->num_philosophers));
    if (philosofe == NULL)
        return ;
    i = 0;  
    while (i < data->num_philosophers)
    {
        pthread_create(&(data->tid) , NULL, &ft_routine, NULL);
        philosofe[i].id = i + 1;
        philosofe[i].num_eat = data->num_eat;
        philosofe[i].is_alive = 1;
        philosofe[i].l_f = &data->forks[philosofe[i].id];
        philosofe[i].r_f = &data->forks[(philosofe[i].id + 1) % data->num_philosophers];
        i++;
    }
    philosofe = data->philo;
    i = 0; 
    while (i < data->num_philosophers)
    {
        printf("philo %d :", philosofe[i].id);
        printf(" num eat %d,", philosofe[i].num_eat);  
        printf(" is alive %d. ", philosofe[i].is_alive);
        printf("\n");
        i++;
    }
}
