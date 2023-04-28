/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:03:00 by abettini          #+#    #+#             */
/*   Updated: 2023/04/28 15:33:35 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//------------------------------------------------------------------------------

long int	ft_time_elapsed(struct timeval time)
{
	long int		time_elapsed;
	struct timeval	time_of_action;

	gettimeofday(&time_of_action, NULL);
	time_elapsed = ((time_of_action.tv_sec * 1000) \
			+ (time_of_action.tv_usec / 1000)) - \
			((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_elapsed);
}

//------------------------------------------------------------------------------

void	ft_mutex_printf(char *str, t_philo *philo)
{
	long int	time_elapsed;

	pthread_mutex_lock(&philo->info->print);
	time_elapsed = ft_time_elapsed(philo->info->start_time);
	if (!philo->info->deaths)
		printf("%ld %d %s\n", time_elapsed, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}
