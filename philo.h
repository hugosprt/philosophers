#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>


typedef enum e_tfk
{
	THINKING,
	EATING,
	SLEEPING,
	TOOK_FORK,
	DEAD
}	t_tfk;


typedef struct s_philo
{
    int     id;
    int		l_fork;
	int		r_fork;
    int     eat;
    int     is_finish;
    int num_eat;
    uint64_t		last_eat;
    struct s_data  *data;
}   t_philo;

typedef struct s_data 
{
    int num_philosophers;
    pthread_mutex_t death;
    int no_one_died;
    int tdie;
    int teat;
    int tsleep;
    int num_eat;
    pthread_mutex_t finish;
    pthread_mutex_t eating;
    pthread_mutex_t write;
    int as_finish; 
    t_philo *philo;
    pthread_mutex_t	*miammiam;
    pthread_t   *tid;
}   t_data;

int    put_struct(t_data *data, char **av);
void	finish(t_data *data);
void    number_philo(t_data *data);
void	print_tfk(t_philo *philo, t_tfk tfk, uint64_t timestamp);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo, uint64_t timestamp);
void	take_forks(t_philo *philo, uint64_t timestamp);
void	leave_forks(t_philo *philo);
uint64_t	get_time(void);

#endif