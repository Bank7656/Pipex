/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 01:04:47 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 13:05:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_syntax(t_arg *arg, const char *s, int *i);
static void		init_arg(t_arg *arg);
static int		parse(t_arg *arg, va_list *ptr, int *count);
static int		ft_option_print(t_arg *arg);

int	ft_printf(const char *s, ...)
{
	int			i;
	int			check;
	int			count;
	t_arg		arg;
	va_list		ptr;

	if (s == NULL)
		return (-1);
	i = 0;
	count = 0;
	check = 0;
	va_start(ptr, s);
	while (s[i] != '\0')
	{
		init_arg(&arg);
		check = check_syntax(&arg, s, &i);
		if (check == -1)
			return (-1);
		else if (check == 0)
			count += write(1, &s[i++], 1);
		else if (parse(&arg, &ptr, &count))
			return (-1);
	}
	va_end(ptr);
	return (count);
}

static void	init_arg(t_arg *arg)
{
	arg -> len = 0;
	arg -> hash = 0;
	arg -> plus = 0;
	arg -> word = 0;
	arg -> zero = 0;
	arg -> minus = 0;
	arg -> space = 0;
	arg -> width = 0;
	arg -> isnull = 0;
	arg -> specifier = 0;
	arg -> precision = -1;
	arg -> width_arg = 0;
	arg -> precision_arg = 0;
}

static int	check_syntax(t_arg *arg, const char *s, int *i)
{
	if (s[*i] != '%' || s[*i] == '\0')
		return (0);
	(*i)++;
	ft_get_specifier(arg, s, i);
	while (s[*i] != '\0')
	{
		if (ft_is_specifier(s[*i]))
		{
			arg -> specifier = s[*i];
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (-1);
}

static int	parse(t_arg *arg, va_list *ptr, int *count)
{
	int	status;

	status = EXIT_SUCCESS;
	ft_get_asterisk_arg(arg, ptr, 0);
	if (arg -> specifier == 'c')
		status = ft_get_char(arg, ptr);
	else if (arg -> specifier == 's')
		status = ft_get_string(arg, ptr);
	else if (arg -> specifier == 'i' || arg -> specifier == 'd')
		status = ft_get_number(arg, ptr);
	else if (arg -> specifier == 'u')
		status = ft_get_unsigned(arg, ptr);
	else if (arg -> specifier == 'x' || arg -> specifier == 'X')
		status = ft_get_hex(arg, ptr);
	else if (arg -> specifier == 'p')
		status = ft_get_memmory(arg, ptr);
	else if (arg -> specifier == '%')
		status = ft_get_percent(arg);
	if (status)
		return (EXIT_FAILURE);
	if (ft_option_print(arg))
		return (EXIT_FAILURE);
	*count += arg -> len;
	return (free(arg -> word), EXIT_SUCCESS);
}

static int	ft_option_print(t_arg *arg)
{
	if (ft_is_precision(arg))
		return (EXIT_FAILURE);
	if (ft_is_plus(arg))
		return (EXIT_FAILURE);
	if (ft_is_sharp(arg))
		return (EXIT_FAILURE);
	if (ft_is_space(arg))
		return (EXIT_FAILURE);
	if (ft_width(arg))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
