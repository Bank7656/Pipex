/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:03:16 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_number(t_arg *arg, va_list *ptr)
{
	int	n;

	n = va_arg(*ptr, int);
	arg -> word = ft_itoa(n);
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	arg -> len = ft_strlen(arg -> word);
	return (EXIT_SUCCESS);
}
