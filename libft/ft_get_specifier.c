/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_specifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:56 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_precision(t_arg *arg, const char *s, int *i);

void	ft_get_specifier(t_arg *arg, const char *s, int *i)
{
	while (ft_is_flag(s[*i]))
		ft_get_flag(arg, s[(*i)++]);
	while (s[*i] == '0')
		(*i)++;
	if (ft_isdigit(s[*i]))
	{
		arg -> width = ft_atoi(s + *i);
		(*i) += ft_count_digit(arg -> width);
	}
	else if (s[*i] == '*')
	{
		arg -> width_arg = 1;
		(*i)++;
	}
	ft_get_precision(arg, s, i);
}

static void	ft_get_precision(t_arg *arg, const char *s, int *i)
{
	if (s[*i] == '.')
	{
		if (ft_isdigit(s[++(*i)]))
		{
			arg -> precision = ft_atoi(s + (*i));
			(*i) += ft_count_digit(arg -> precision);
		}
		else if (s[*i] == '*')
		{
			arg -> precision_arg = 1;
			(*i)++;
		}
		else
			arg -> precision = 0;
	}
}

void	ft_get_asterisk_arg(t_arg *arg, va_list *ptr, int n)
{
	if (arg -> width_arg)
	{
		n = va_arg(*ptr, int);
		if (n >= 0)
			arg -> width = n;
		else
		{
			arg -> width = n * (-1);
			arg -> minus = 1;
		}
	}
	if (arg -> precision_arg)
	{
		n = va_arg(*ptr, int);
		if (n > 0)
			arg -> precision = n;
		else if (n == 0)
		{
			arg -> zero = 0;
			arg -> precision = 0;
		}
		else
			arg -> precision = -1;
	}
}
