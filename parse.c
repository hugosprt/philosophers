#include "philo.h"

void ft_error()
{
    write(2, "error\n", 6);
}

static	int	ft_isdigit2(char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

long	int	ft_atol(const char *str)
{
	int			i;
	long int	nb;
	int			sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (str[i] && ((str[i] <= 13 && str[i] >= 9) || str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '+' && ft_isdigit2(str[i + 1]))
		i++;
	if (str[i] == '-' && ft_isdigit2(str[i + 1]))
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit2(str[i]))
	{
		nb = str[i] - 48 + nb * 10;
		i++;
	}
	return (nb * sign);
}


int parse(char **av)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (!ft_isdigit2(av[i][j]) && av[i][j])
            {
               
                ft_error();
                return (0);
            }
            j++;
        }
        i++;
    }
    if (i == 5 || i == 6)
        return (1);
    ft_error();
    return (0);
}


void    put_struct(t_data *data, char **av)
{
    if (!parse(av))
        return ;
    else
    {
       data->number_of_philosophers = ft_atol(av[1]);
       data->time_to_die = ft_atol(av[2]);
       data->time_to_eat = ft_atol(av[3]);
       data->time_to_sleep = ft_atol(av[4]);
       if (av[5])
            data->number_of_times_each_philosopher_must_eat = ft_atol(av[5]);
    }
}