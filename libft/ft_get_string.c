/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:10:07 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_string(t_arg *arg, va_list *ptr)
{
	char	*word;

	word = va_arg(*ptr, char *);
	if (word == NULL)
	{
		arg -> isnull = 1;
		arg -> word = ft_strdup("(null)");
		if (arg -> word == NULL)
			return (EXIT_FAILURE);
		arg -> len = ft_strlen(arg -> word);
		return (EXIT_SUCCESS);
	}
	arg -> len = ft_strlen(word);
	arg -> word = ft_strdup(word);
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
