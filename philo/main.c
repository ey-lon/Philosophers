/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:15:13 by abettini          #+#    #+#             */
/*   Updated: 2023/04/28 15:05:16 by abettini         ###   ########.fr       */
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

void    ft_philos_join(t_philo *philos, int n_of_philos)
{
    int i;

    i = 0;
    while (i < n_of_philos)
    {
        pthread_join(philos[i].philo, NULL);
        i++;
    }
}

void    ft_philos_end(t_philo *philos, int n_of_philos)
{
    int i;

    i = 0;
    while (i < n_of_philos)
    {
        pthread_mutex_destroy(&philos[i].fork_l);
        i++;
    }
    free(philos);
}

//---------------------------------------------------------------------------------------------------------------

void    ft_philos_init(t_philo *philos, int n_of_philos, t_vars *info)
{
    int i;

    i = 0;
    while (i < n_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].full = 0;
        philos[i].meals_left = info->n_meals;
        philos[i].last_meal = info->start_time;
        pthread_mutex_init(&philos[i].fork_l, NULL);
        if (i + 1 < n_of_philos)
            philos[i].fork_r = &philos[i + 1].fork_l;
        else
            philos[i].fork_r = &philos[0].fork_l;
        philos[i].info = info;
        i++;
    }
}

void    ft_philos_start(t_philo *philos, int n_of_philos)
{
    int i;

    i = 0;
    while (i < n_of_philos)
    {
        pthread_create(&philos[i].philo, NULL, ft_philo, &philos[i]);
        i += 2;
    }
    usleep(1000);
    i = 1;
    while (i < n_of_philos)
    {
        pthread_create(&philos[i].philo, NULL, ft_philo, &philos[i]);
        i += 2;
    }
}

//---------------------------------------------------------------------------------------------------------------

t_vars  ft_get_info(int ac, char **av)
{
    t_vars info;

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

int main(int ac, char **av)
{
    t_vars info;
    t_philo *philos;
    pthread_t death;

    if (ac < 5 || ac > 6)
        return (1);
    if (ft_error_check(av + 1))
        return (printf("Error!\n") * 0 + 2);
    info = ft_get_info(ac - 1, av + 1);
    philos = malloc(sizeof(t_philo) * info.n_of_philos);
    pthread_mutex_init(&info.print, NULL);
    pthread_mutex_init(&info.meal, NULL);
    gettimeofday(&info.start_time, NULL);
    ft_philos_init(philos, info.n_of_philos, &info);
    if (info.n_of_philos > 1)
        ft_philos_start(philos, info.n_of_philos);
    else
        pthread_create(&philos->philo, NULL, ft_one_philo, philos);
    pthread_create(&death, NULL, ft_philos_death, philos);
    ft_philos_join(philos, info.n_of_philos);
    ft_philos_end(philos, info.n_of_philos);
    //handle end.
    return (0);
}

//pthread_join needed for the leaks!!
