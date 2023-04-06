/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettini <abettini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:19:31 by abettini          #+#    #+#             */
/*   Updated: 2023/04/06 10:05:14 by abettini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_int_limit_check(char *str)
{
	long long	res;
	int			sign;
	int			i;
	int			dig_n;	

	dig_n = 0;
	res = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && dig_n <= 11)
	{
		res = res * 10 + str[i] - '0';
		i++;
		dig_n++;
	}
	if (dig_n > 10 || res * sign > INT_MAX || res * sign < INT_MIN)
		return (1);
	return (0);
}

int	ft_int_type_check(char *str)
{
	int	i;
	int	check;

	check = 0;
	if (((str[0] == '-' || str[0] == '+')
			&& str[1] != '\0') || ft_isdigit(str[0]))
	{
		i = 1;
		while (str[i] && check == 0)
		{
			if (!ft_isdigit(str[i]))
				check = 1;
			i++;
		}
	}
	else
		check = 1;
	return (check);
}

int	ft_negative_check(char *str)
{
	if (ft_atoi(str) < 0)
		return (1);
	return (0);
}

int	ft_error_check(char **mat)
{
	int	check;
	int	y;

	check = 0;
	if (mat && mat[0])
	{
		y = 0;
		while (mat[y] && !check)
		{
			check += ft_int_type_check(mat[y]);
			check += ft_int_limit_check(mat[y]);
			check += ft_negative_check(mat[y]);
			y++;
		}
		return (check);
	}
	return (1);
}
