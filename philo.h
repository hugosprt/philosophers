#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_data
{
	int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    int number_of_fourchette;
    //t_philo[number_of_philosophers];
}       t_data;

// typedef struct t_philo 
// {

// }   s_philo;
void    put_struct(t_data *data, char **av);


#endif