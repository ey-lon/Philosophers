/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:43:52 by abettini          #+#    #+#             */
/*   Updated: 2023/05/05 12:16:12 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_philos_join(t_philo *philos, int n_of_philos)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

static void	ft_philos_end(t_philo *philos, int n_of_philos)
{
	int	i;

	pthread_mutex_destroy(&philos->info->print);
	pthread_mutex_destroy(&philos->info->meal);
	i = 0;
	while (i < n_of_philos)
	{
		pthread_mutex_destroy(&philos[i].fork_l);
		i++;
	}
	free(philos);
}

//-----------------------------------------------------------------------------

static void	ft_philos_init(t_philo *philos, int n_of_philos, t_vars *info)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		philos[i].id = i + 1;
		if (!info->n_meals)
			philos[i].full = 1;
		else
			philos[i].full = 0;
		philos[i].meals_left = info->n_meals;
		pthread_mutex_init(&philos[i].fork_l, NULL);
		if (i + 1 < n_of_philos)
			philos[i].fork_r = &philos[i + 1].fork_l;
		else
			philos[i].fork_r = &philos[0].fork_l;
		philos[i].info = info;
		i++;
	}
}

static void	ft_philos_start(t_philo *philos, int n_of_philos)
{
	int	i;

	i = 0;
	while (i < n_of_philos)
	{
		if (i % 2 == 1)
			usleep (100);
		gettimeofday(&philos[i].last_meal, NULL);
		pthread_create(&philos[i].philo, NULL, ft_philo, &philos[i]);
		i += 1;
	}
}

void	ft_philo_main(t_philo *philos, t_vars *info)
{
	pthread_t	death;

	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->meal, NULL);
	gettimeofday(&info->start_time, NULL);
	ft_philos_init(philos, info->n_of_philos, info);
	if (info->n_of_philos > 1)
		ft_philos_start(philos, info->n_of_philos);
	else
		pthread_create(&philos->philo, NULL, ft_one_philo, philos);
	usleep(1000);
	if (info->n_meals)
	{
		pthread_create(&death, NULL, ft_philos_death, philos);
		pthread_join(death, NULL);
	}
	ft_philos_join(philos, info->n_of_philos);
	ft_philos_end(philos, info->n_of_philos);
}
