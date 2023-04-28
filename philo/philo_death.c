/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:53:55 by abettini          #+#    #+#             */
/*   Updated: 2023/04/28 15:11:42 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//-----------------------------------------------------------------------------

int     ft_check_death(t_philo *philo)
{
    struct timeval time;
    int             check;

    check = 0;
    gettimeofday(&time, NULL);
    pthread_mutex_lock(&philo->info->meal);
    if (!philo->full && \
		ft_time_elapsed(philo->last_meal) >= philo->info->time_to_die)
        check = 1;
    pthread_mutex_unlock(&philo->info->meal);
    return (check);
}

void    *ft_philos_death(void *arg)
{
    t_philo *philos;
    int i;
    
    philos = (t_philo *)arg;
    i = 0;
    while (1)
    {
        if (ft_check_death(&philos[i]))
        {
            pthread_mutex_lock(&philos->info->print);
            printf("%ld %d %s\n", ft_time_elapsed(philos->info->start_time), \
				philos[i].id, "died");
            philos->info->deaths++;
            pthread_mutex_unlock(&philos->info->print);
            return (NULL);
        }
        i++;
        if (i == philos->info->n_of_philos)
            i = 0;
    }
    return (NULL);
}