/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:44:15 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_zero_padding(t_arg *arg);
static void	minus_flag(t_arg *arg, char c, int length);
static void	print_width(t_arg *arg, char c, int length);

int	ft_width(t_arg *arg)
{
	char	c;

	c = ' ';
	if (arg -> specifier == '%')
	{
		write(1, arg -> word, 1);
		return (EXIT_SUCCESS);
	}
	if (arg -> zero && check_zero_padding(arg))
	{
		c = '0';
		if (zero_number(arg))
			return (EXIT_FAILURE);
		if (zero_hex(arg))
			return (EXIT_FAILURE);
		if (zero_space(arg))
			return (EXIT_FAILURE);
	}
	if (arg -> minus)
		minus_flag(arg, c, arg -> len);
	else
		print_width(arg, c, arg -> len);
	return (EXIT_SUCCESS);
}

static int	check_zero_padding(t_arg *arg)
{
	if (arg -> zero && arg -> minus)
		return (0);
	if (arg -> zero && arg -> precision != -1)
		return (0);
	return (1);
}

static void	minus_flag(t_arg *arg, char c, int length)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (arg -> specifier == 'c' && arg -> word[0] == '\0')
		write(1, &arg -> word[0], 1);
	while (arg -> word[++j] != '\0')
		write(1, &arg -> word[j], 1);
	while (length + (++i) < (arg -> width))
		arg -> len += write(1, &c, 1);
}

static void	print_width(t_arg *arg, char c, int length)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < (arg -> width) - length)
		arg -> len += write(1, &c, 1);
	while (arg -> word[++j] != '\0')
		write(1, &arg -> word[j], 1);
	if (arg -> specifier == 'c' && arg -> word[0] == '\0')
		write(1, &arg -> word[0], 1);
}
