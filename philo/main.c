/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:15:13 by abettini          #+#    #+#             */
/*   Updated: 2023/05/05 11:41:56 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//-----------------------------------------------------------------------------

static t_vars	ft_get_info(int ac, char **av)
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
		return (printf("Error!\nInvalid number of arguments\n") * 0 + 1);
	if (ft_error_check(av + 1))
		return (printf("Error!\n") * 0 + 2);
	info = ft_get_info(ac - 1, av + 1);
	philos = malloc(sizeof(t_philo) * info.n_of_philos);
	ft_philo_main(philos, &info);
	return (0);
}
