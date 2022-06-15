#include "philo.h"

void    number_philo(t_data *data)
{
    int i;
   

    data->philo = malloc(sizeof(t_philo));
    if (data->philo == NULL)
        return ;
    i = 0;  
    while (i <= data->num_philosophers)
    {
        data->philo[i].id = i;
        data->philo[i].num_eat = 0;
        data->philo[i].is_alive = 1;
        i++;
    }
    i = 0;  
    while (i <= data->num_philosophers)
    {
        printf("philo %d :", data->philo[i].id);
        printf(" num eat%d,", data->philo[i].num_eat);  
        printf(" is alive %d ", data->philo[i].is_alive);
        i++;
    }
}
