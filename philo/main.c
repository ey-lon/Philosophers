/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:15:13 by abettini          #+#    #+#             */
/*   Updated: 2023/04/06 12:11:16 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    ft_philos_join(t_philo *philos, int n_of_philos)
{
    int i;

    i = -1;
    while (++i < n_of_philos)
        pthread_join(philos[i].philo, NULL);
}

void    ft_philos_detach(t_philo *philos, int n_of_philos)
{
    int i;

    i = -1;
    while (++i < n_of_philos)
    {
        pthread_detach(philos[i].philo);
        pthread_mutex_unlock(&philos[i].fork_l);
    }
}

void    ft_philos_end(t_philo *philos, int n_of_philos)
{
    int i;

    i = -1;
    while (++i < n_of_philos)
        pthread_mutex_destroy(&philos[i].fork_l);
    free(philos);
    exit (0);
}

//---------------------------------------------------------------------------------------------------------------

void *ft_philo(void *arg)
{
    t_philo *philo;
    struct timeval time_of_action;

    philo = (t_philo *)arg;
    while ((philo->info->number_of_times_each_philo_must_eat == -1) \
        || (philo->number_of_times_philo_has_eaten < philo->info->number_of_times_each_philo_must_eat))
    {
        //philosopher is thinking -------------------------------------------------------------------------------
        gettimeofday(&time_of_action, NULL);
        printf("%ld %d is thinking\n", time_of_action.tv_usec - philo->info->start_time.tv_usec, philo->id);
        usleep(0);
        //philosopher is eating ---------------------------------------------------------------------------------
        pthread_mutex_lock(&philo->fork_l);
        //////////////////////////////////////////////////////////////////////////
        //if (philo->info->deaths > 0)
        //    return (NULL);
        gettimeofday(&time_of_action, NULL);
        printf("%ld %d has taken a fork\n", time_of_action.tv_usec - philo->info->start_time.tv_usec, philo->id);
        pthread_mutex_lock(philo->fork_r);
        //////////////////////////////////////////////////////////////////////////
        //if (philo->info->deaths > 0)
        //    return (NULL);
        gettimeofday(&time_of_action, NULL);
        printf("%ld %d has taken a fork\n", time_of_action.tv_usec - philo->info->start_time.tv_usec, philo->id);
        printf("%ld %d is eating\n", time_of_action.tv_usec - philo->info->start_time.tv_usec, philo->id);
        usleep(philo->info->time_to_eat);
        gettimeofday(&philo->last_time_philo_has_eaten, NULL);
        philo->number_of_times_philo_has_eaten++;
        pthread_mutex_unlock(&philo->fork_l);
        pthread_mutex_unlock(philo->fork_r);
        //philosopher is sleeping -------------------------------------------------------------------------------
        gettimeofday(&time_of_action, NULL);
        printf("%ld %d is sleeping\n", time_of_action.tv_usec - philo->info->start_time.tv_usec, philo->id);
        usleep(philo->info->time_to_sleep);
    }
    return (NULL);
}

//---------------------------------------------------------------------------------------------------------------

void    *ft_philos_death(void *arg)
{
    t_philo *philos;
    struct timeval time;
    int i;
    
    philos = (t_philo *)arg;
    i = -1;
    while (1)
    {
        i++;
        gettimeofday(&time, NULL);
        if (time.tv_usec - philos[i].last_time_philo_has_eaten.tv_usec >= philos->info->time_to_die)
        {
            printf("%ld %d died\n", time.tv_usec - philos->info->start_time.tv_usec, philos[i].id);
            ////////////////////////////////////////////////////////////////////////////
            ft_philos_end(philos, philos->info->n_of_philos);
            return (NULL);
        }
        if (i == philos[i].info->n_of_philos - 1)
            i = -1;
    }
    return (NULL);
}

//---------------------------------------------------------------------------------------------------------------

void    ft_philos_init(t_philo *philos, int n_of_philos, t_vars *info)
{
    int i;

    i = -1;
    while (++i < n_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].number_of_times_philo_has_eaten = 0;
        gettimeofday(&philos[i].last_time_philo_has_eaten, NULL);
        pthread_create(&philos[i].philo, NULL, ft_philo, &philos[i]);
        pthread_mutex_init(&philos[i].fork_l, NULL);
        if (i + 1 < n_of_philos)
            philos[i].fork_r = &philos[i+1].fork_l;
        else
            philos[i].fork_r = &philos[0].fork_l;
        philos[i].info = info;
    }
}

//---------------------------------------------------------------------------------------------------------------

t_vars  ft_get_stats(int ac, char **av)
{
    t_vars info;

    //info.deaths = 0;
    info.n_of_philos = ft_atoi(av[0]);
    info.time_to_die = ft_atoi(av[1]);
    info.time_to_eat = ft_atoi(av[2]);
    info.time_to_sleep = ft_atoi(av[3]);
    if (ac == 5)
        info.number_of_times_each_philo_must_eat = ft_atoi(av[4]);
    else
        info.number_of_times_each_philo_must_eat = -1;
    return (info);
}

int main(int ac, char **av)
{
    t_vars info;
    t_philo *philos;
    pthread_t death;

    if (ac < 5 || ac > 7)
        return (1);
    if (ft_error_check(av + 1))
        return (printf("Error!\n") * 0 + 2);
    info = ft_get_stats(ac - 1, av + 1);
    philos = malloc(sizeof(t_philo) * info.n_of_philos);
    gettimeofday(&info.start_time, NULL);
    ft_philos_init(philos, info.n_of_philos, &info);
    pthread_create(&death, NULL, ft_philos_death, philos);
    ft_philos_join(philos, info.n_of_philos);
    ft_philos_end(philos, info.n_of_philos);
    return (0);
}
