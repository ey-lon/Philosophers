/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:15:13 by abettini          #+#    #+#             */
/*   Updated: 2023/05/02 13:50:46 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
void    ft_philos_detach(t_philo *philos, int n_of_philos)
{
    int i;

    i = 0;
    while (i < n_of_philos)
    {
        pthread_detach(philos[i].philo);
        i++;
    }
}
*/
/*
void    ft_forks_unlock(t_philo *philos, int n_of_philos)
{
    int i;

    i = 0;
    while (1)
    {
        pthread_mutex_unlock(&philos[i].fork_l);
        i++;
        if (i == n_of_philos)
            i = 0;
    }
}
*/

//-----------------------------------------------------------------------------

t_vars	ft_get_info(int ac, char **av)
{
	t_vars	info;

	info.deaths = 0;
	info.n_of_philos = ft_atoi(av[0]);
	info.time_to_die = ft_atoi(av[1]);
	info.time_to_eat = ft_atoi(av[2]);
	info.time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		info.n_meals = ft_atoi(av[4]);
	else
		info.n_meals = -1;
	return (info);
}

int	main(int ac, char **av)
{
	t_vars		info;
	t_philo		*philos;

	if (ac < 5 || ac > 6)
		return (1);
	if (ft_error_check(av + 1))
		return (printf("Error!\n") * 0 + 2);
	info = ft_get_info(ac - 1, av + 1);
	philos = malloc(sizeof(t_philo) * info.n_of_philos);
	ft_philo_main(philos, &info);
	return (0);
}

//pthread_join needed for the leaks!!
