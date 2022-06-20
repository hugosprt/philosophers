#include "philo.h"

int main( int ac, char **av)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    (void)(ac);
    if (put_struct(data, av))
        number_philo(data);
    finish(data);
    return (0);
}