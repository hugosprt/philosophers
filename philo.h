#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>


typedef struct s_philo
{
    int     id;
    int     num_eat;
    int is_alive;
    int is_eating;
    int is_sleep;
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
}   t_data;

void    put_struct(t_data *data, char **av);

void    number_philo(t_data *data);

#endif