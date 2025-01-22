/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:05:00 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/16 19:22:48 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_number(const char *str, int sign);

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	int		number;

	i = 0;
	sign = 0;
	number = 0;
	if (nptr == NULL)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	while (nptr[i] == '-' || nptr[i] == '+')
	{
		if (sign != 0)
			return (0);
		if (nptr[i++] == '-')
			sign = -1;
		else
			sign = 1;
	}
	if (sign == 0)
		sign = 1;
	number = ft_atoi_number(nptr + i, sign);
	return (number);
}

static int	ft_atoi_number(const char *str, int sign)
{
	int		i;
	int		number;
	long	tmp;

	i = 0;
	tmp = 0;
	number = 0;
	while (ft_isdigit(str[i]))
	{
		tmp = (tmp * 10) + str[i] - '0';
		i++;
	}
	if (tmp > INT_MAX && (tmp * sign != INT_MIN))
		number = 0;
	else if (tmp * sign == INT_MIN)
		return (INT_MIN);
	else if (tmp < INT_MIN)
		number = 0;
	else
		number = tmp;
	return (number * sign);
}
