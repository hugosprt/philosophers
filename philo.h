#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_philo
{
    int     id;
    int     eat;
    int is_alive;
    int is_eating;
    int is_sleep;
    
    struct s_data  *data;
}   t_philo;

typedef struct s_data 
{
    int num_philosophers;
    int tdie;
    int teat;
    int tsleep;
    int num_eat;
    int num_fourchette;
    t_philo *philo;
    pthread_mutex_t	*miammiam;
    pthread_t   *tid;
}   t_data;

int    put_struct(t_data *data, char **av);
void	finish(t_data *data);
void    number_philo(t_data *data);

#endif