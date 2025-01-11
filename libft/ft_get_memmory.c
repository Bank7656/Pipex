/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_memmory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:40:12 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 13:22:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		mem_len(unsigned long n);
static char		get_mem_hex(int n);
static void		assign_number(t_arg *arg, unsigned long n);
unsigned long	ft_mem_power(unsigned long base, int n);

int	ft_get_memmory(t_arg *arg, va_list *ptr)
{
	unsigned long	n;

	n = (unsigned long)va_arg(*ptr, void *);
	if (n == 0)
	{
		arg -> word = ft_strdup(NULL_PTR);
		if (arg -> word == NULL)
			return (EXIT_FAILURE);
		arg -> len = ft_strlen(arg -> word);
		return (EXIT_SUCCESS);
	}
	arg -> len = mem_len(n);
	arg -> word = (char *)malloc(sizeof(char) * (arg -> len + 3));
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	assign_number(arg, n);
	return (EXIT_SUCCESS);
}

static void	assign_number(t_arg *arg, unsigned long n)
{
	int	i;
	int	tmp;

	i = 0;
	arg -> word[0] = '0';
	arg -> word[1] = 'x';
	while (i < arg -> len)
	{
		tmp = n / ft_mem_power(16, (arg -> len - i - 1)) % 16;
		arg -> word[i + 2] = get_mem_hex(tmp);
		i++;
	}
	arg -> word[i + 2] = '\0';
	arg -> len += 2;
}

static int	mem_len(unsigned long n)
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

static char	get_mem_hex(int n)
{
	char	*hex;

	hex = "0123456789abcdef";
	return (hex[n]);
}

unsigned long	ft_mem_power(unsigned long base, int n)
{
	if (n < 0)
		return (0);
	if (base == 0 || n == 0)
		return (1);
	return (base * ft_mem_power(base, n - 1));
}
