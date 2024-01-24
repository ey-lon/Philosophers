/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:19:31 by abettini          #+#    #+#             */
/*   Updated: 2024/01/24 15:50:10 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	ft_int_limit_check(char *str)
{
	long long	res;
	int			sign;
	int			i;	

	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign > INT_MAX || res * sign < INT_MIN);
}

static bool	ft_int_type_check(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static bool	ft_negative_check(char *str)
{
	return (ft_atoi(str) < 0);
}

bool	ft_error_check(char **mat)
{
	int	y;

	if (mat && mat[0])
	{
		y = 0;
		while (mat[y])
		{
			if (ft_int_type_check(mat[y]))
				return (1);
			if (ft_int_limit_check(mat[y]))
				return (1);
			if (ft_negative_check(mat[y]))
				return (1);
			y++;
		}
		return (0);
	}
	return (1);
}
