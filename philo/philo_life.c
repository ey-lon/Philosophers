/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:55:17 by abettini          #+#    #+#             */
/*   Updated: 2023/04/28 15:42:54 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//-----------------------------------------------------------------------------

int	ft_philo_full(t_philo *philo)
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

int	ft_check_death(t_philo *philo)
{
	int	check;

	check = 0;
	pthread_mutex_lock(&philo->info->print);
	if (philo->info->deaths)
		check = 1;
	pthread_mutex_unlock(&philo->info->print);
	return (check);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while ((philo->info->n_meals == -1 || philo->meals_left) \
			&& !ft_check_death(philo))
	{
		pthread_mutex_lock(&philo->fork_l);
		ft_mutex_printf("has taken a fork", philo);
		pthread_mutex_lock(philo->fork_r);
		ft_mutex_printf("has taken a fork", philo);
		ft_mutex_printf("is eating", philo);
		gettimeofday(&philo->last_meal, NULL);
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

void	*ft_one_philo(void *arg)
{
	t_philo	*philo;
	int		death_check;

	philo = (t_philo *)arg;
	if (!philo->meals_left)
		return (NULL);
	ft_mutex_printf("is thinking", philo);
	usleep(0);
	ft_mutex_printf("has taken a fork", philo);
	pthread_mutex_lock(&philo->fork_l);
	if (!philo->meals_left)
		return (NULL);
	death_check = 0;
	while (!death_check)
	{
		pthread_mutex_lock(&philo->info->print);
		if (philo->info->deaths)
			death_check++;
		pthread_mutex_unlock(&philo->info->print);
	}
	return (NULL);
}
