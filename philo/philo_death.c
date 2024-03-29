/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:53:55 by abettini          #+#    #+#             */
/*   Updated: 2024/01/24 15:36:58 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//-----------------------------------------------------------------------------

static bool	ft_check_starve(t_philo *philo)
{
	struct timeval	time;
	bool			check;

	check = 0;
	gettimeofday(&time, NULL);
	pthread_mutex_lock(&philo->info->meal);
	if (!philo->full && \
		ft_time_elapsed(philo->last_meal) >= philo->info->time_to_die)
		check = 1;
	pthread_mutex_unlock(&philo->info->meal);
	return (check);
}

static bool	ft_check_full(t_philo *philos)
{
	bool		check;
	static int	count;

	check = 0;
	pthread_mutex_lock(&philos->info->meal);
	while (philos[count].full)
		count++;
	if (count == philos->info->n_of_philos)
	{
		check = 1;
		pthread_mutex_lock(&philos->info->print);
		printf("All philos ate %d times\n", philos->info->n_meals);
		pthread_mutex_unlock(&philos->info->print);
	}
	pthread_mutex_unlock(&philos->info->meal);
	return (check);
}

//-----------------------------------------------------------------------------

void	*ft_philos_death(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	i = 0;
	while (!ft_check_full(philos))
	{
		if (ft_check_starve(&philos[i]))
		{
			pthread_mutex_lock(&philos->info->print);
			printf("%ld %d %s\n", ft_time_elapsed(philos->info->start_time), \
				philos[i].id, "died");
			philos->info->deaths = 1;
			pthread_mutex_unlock(&philos->info->print);
			break ;
		}
		i++;
		if (i == philos->info->n_of_philos)
			i = 0;
		usleep(0);
	}
	return (NULL);
}
