/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:15:13 by abettini          #+#    #+#             */
/*   Updated: 2023/04/24 15:39:58 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


/*
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
*/

//---------------------------------------------------------------------------------------------------------------

long int ft_time_elapsed(struct timeval time)
{
    long int        x;
    struct timeval  time_of_action;

    gettimeofday(&time_of_action, NULL);
    x = time_of_action.tv_usec - time.tv_usec;
    return (x);
}

void    ft_mutex_printf(char *str, t_philo *philo)
{   
    pthread_mutex_lock(&philo->info->print);
    printf("%ld %d %s\n", ft_time_elapsed(philo->info->start_time), philo->id, str);
    pthread_mutex_unlock(&philo->info->print);
}

//---------------------------------------------------------------------------------------------------------------

void *ft_philo(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (((philo->info->number_of_times_each_philo_must_eat == -1) \
        || (philo->number_of_times_philo_has_eaten < philo->info->number_of_times_each_philo_must_eat)) &&
        !philo->info->deaths)
    {
        //philosopher is thinking -------------------------------------------------------------------------------
        ft_mutex_printf("is thinking", philo);
        usleep(0);
        //philosopher is eating ---------------------------------------------------------------------------------
        pthread_mutex_lock(&philo->fork_l);
        ft_mutex_printf("has taken a fork", philo);
        pthread_mutex_lock(philo->fork_r);
        ft_mutex_printf("has taken a fork", philo);
        ft_mutex_printf("is eating", philo);
        gettimeofday(&philo->last_time_philo_has_eaten, NULL);
        usleep(philo->info->time_to_eat * 1000);
        philo->number_of_times_philo_has_eaten++;
        pthread_mutex_unlock(&philo->fork_l);
        pthread_mutex_unlock(philo->fork_r);
        //philosopher is sleeping -------------------------------------------------------------------------------
        ft_mutex_printf("is sleeping", philo);
        usleep(philo->info->time_to_sleep * 1000);
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
    i = 0;
    while (1)
    {
        gettimeofday(&time, NULL);
        if (time.tv_usec - philos[i].last_time_philo_has_eaten.tv_usec >= philos->info->time_to_die)
        {
            pthread_mutex_lock(&philos->info->print);
            printf("%ld %d %s\n", ft_time_elapsed(philos->info->start_time), philos[i].id, "died");
            philos->info->deaths++;
            return (NULL);
        }
        i++;
        if (i == philos->info->n_of_philos)
            i = 0;
    }
    return (NULL);
}

//---------------------------------------------------------------------------------------------------------------

void    ft_philos_init(t_philo *philos, int n_of_philos, t_vars *info)
{
    int i;

    i = 0;
    while (i < n_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].number_of_times_philo_has_eaten = 0;
        gettimeofday(&philos[i].last_time_philo_has_eaten, NULL);
        pthread_create(&philos[i].philo, NULL, ft_philo, &philos[i]);
        pthread_mutex_init(&philos[i].fork_l, NULL);
        if (i + 1 < n_of_philos)
            philos[i].fork_r = &philos[i + 1].fork_l;
        else
            philos[i].fork_r = &philos[0].fork_l;
        philos[i].info = info;
        i++;
    }
}

//---------------------------------------------------------------------------------------------------------------

t_vars  ft_get_stats(int ac, char **av)
{
    t_vars info;

    info.deaths = 0;
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

    if (ac < 5 || ac > 6)
        return (1);
    if (ft_error_check(av + 1))
        return (printf("Error!\n") * 0 + 2);
    info = ft_get_stats(ac - 1, av + 1);
    philos = malloc(sizeof(t_philo) * info.n_of_philos);
    pthread_mutex_init(&info.print, NULL);
    gettimeofday(&info.start_time, NULL);
    ft_philos_init(philos, info.n_of_philos, &info);
    pthread_create(&death, NULL, ft_philos_death, philos);
    while (!info.deaths)
        usleep(0);
    //handle end.
    return (0);
}

//pthread_join needed for the leaks!!
