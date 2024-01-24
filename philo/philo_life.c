/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:55:17 by abettini          #+#    #+#             */
/*   Updated: 2024/01/24 15:43:19 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//------------------------------------------------------------------------------

static bool	ft_philo_full(t_philo *philo)
{
	if (!philo->meals_left)
	{
		pthread_mutex_lock(&philo->info->meal);
		philo->full = 1;
		pthread_mutex_unlock(&philo->info->meal);
		return (1);
	}
	return (0);
}

static bool	ft_check_deaths(t_philo *philo)
{
	bool	check;

	check = 0;
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->deaths)
		check = 1;
	pthread_mutex_unlock(&philo->info->print);
	return (check);
}

//------------------------------------------------------------------------------

static void	ft_eat(pthread_mutex_t *m1, pthread_mutex_t *m2, t_philo *philo)
{
	if (philo->info->n_of_philos % 2 == 1 \
		&& philo->id == philo->info->n_of_philos - 1)
	{
		usleep(1000);
	}
	if (m1 < m2)
	{
		pthread_mutex_lock(m1);
		ft_mutex_printf("has taken left fork", philo);
		pthread_mutex_lock(m2);
		ft_mutex_printf("has taken right fork", philo);
	}
	else
	{
		pthread_mutex_lock(m2);
		ft_mutex_printf("has taken right fork", philo);
		pthread_mutex_lock(m1);
		ft_mutex_printf("has taken left fork", philo);
	}
	ft_mutex_printf("is eating", philo);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((philo->info->n_meals == -1 || philo->meals_left) \
			&& !ft_check_deaths(philo))
	{
		ft_eat(&philo->fork_l, philo->fork_r, philo);
		pthread_mutex_lock(&philo->info->meal);
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(&philo->info->meal);
		usleep(philo->info->time_to_eat * 1000);
		if (philo->meals_left != -1)
			philo->meals_left--;
		pthread_mutex_unlock(&philo->fork_l);
		pthread_mutex_unlock(philo->fork_r);
		if (ft_philo_full(philo))
			break ;
		ft_mutex_printf("is sleeping", philo);
		usleep(philo->info->time_to_sleep * 1000);
		ft_mutex_printf("is thinking", philo);
	}
	return (NULL);
}

//-----------------------------------------------------------------------------

void	*ft_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->info->meal);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->info->meal);
	if (!philo->meals_left)
		return (NULL);
	ft_mutex_printf("has taken a fork", philo);
	usleep(philo->info->time_to_die * 1000);
	ft_mutex_printf("died", philo);
	return (NULL);
}
