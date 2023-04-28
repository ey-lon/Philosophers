/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 09:56:28 by abettini          #+#    #+#             */
/*   Updated: 2023/04/28 12:15:34 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <time.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_vars
{
	int			n_of_philos;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int			n_meals;
	struct timeval	start_time;
	int			deaths;
	pthread_mutex_t print;
}	t_vars;

typedef struct s_philo
{
	int				id;
	pthread_t		philo;
	pthread_mutex_t fork_l;
	pthread_mutex_t *fork_r;
	int				meals_left;
	struct timeval	last_meal;
	t_vars			*info;
} t_philo;

//err_check -----------------------------
int	ft_error_check(char **mat);
//utils ---------------------------------
int	ft_atoi(const char *str);
int	ft_isdigit(char c);

#endif
