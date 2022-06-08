#include "philo.h"

int main( int ac, char **av)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    (void)(ac);
    put_struct(data, av);
}