/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:44:00 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/15 01:38:16 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_unsigned_to_string(unsigned int n);
static int	find_num_len(unsigned int n);
static void	convert(char *arr, unsigned int n, int len);

int	ft_get_unsigned(t_arg *arg, va_list *ptr)
{
	unsigned int	n;

	n = va_arg(*ptr, unsigned int);
	arg -> word = ft_unsigned_to_string(n);
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	arg -> len = ft_strlen(arg -> word);
	return (EXIT_SUCCESS);
}

static char	*ft_unsigned_to_string(unsigned int n)
{
	int		len;
	char	*number;

	len = find_num_len(n);
	number = (char *)malloc(sizeof(char) * (len + 1));
	if (number == NULL)
		return (NULL);
	convert(number, n, len);
	return (number);
}

static int	find_num_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if ((int)n < 0)
		n = UINT32_MAX + n + 1;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	convert(char *arr, unsigned int n, int len)
{
	int	i;

	i = 0;
	if ((int)n < 0)
		n = UINT32_MAX + n + 1;
	while (i < len)
	{
		arr[i] = ((n / ft_power(10, len - 1 - i)) % 10) + 48;
		i++;
	}
	arr[i] = '\0';
}
