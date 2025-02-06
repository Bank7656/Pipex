/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:16:17 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_len(unsigned int n);
static char	get_hex(int n, char specifier);

int	ft_get_hex(t_arg *arg, va_list *ptr)
{
	int				i;
	int				tmp;
	unsigned int	n;

	n = va_arg(*ptr, unsigned int);
	if (n == 0)
		arg -> isnull = 1;
	arg -> len = hex_len(n);
	arg -> word = (char *)malloc(sizeof(char) * (arg -> len + 1));
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < arg -> len)
	{
		tmp = n / ft_power(16, (arg -> len - i - 1)) % 16;
		arg -> word[i] = get_hex((tmp), arg -> specifier);
		i++;
	}
	arg -> word[i] = '\0';
	return (EXIT_SUCCESS);
}

static int	hex_len(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		count++;
		n = n / 16;
	}
	return (count);
}

static char	get_hex(int n, char specifier)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (specifier == 'x')
		return (hex[n]);
	else
		return (ft_toupper(hex[n]));
}
