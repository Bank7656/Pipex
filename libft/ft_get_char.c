/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 01:07:10 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_char(t_arg *arg, va_list *ptr)
{
	int	c;

	c = va_arg(*ptr, int);
	arg -> len = 1;
	arg -> word = (char *)ft_calloc(arg -> len, sizeof(char) + 1);
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	arg -> word[0] = c;
	arg -> word[1] = '\0';
	return (EXIT_SUCCESS);
}
