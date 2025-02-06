/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_plus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:11:05 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_plus(t_arg *arg)
{
	char	*tmp;

	if (arg -> plus && (arg -> word[0] != '-')
		&& ((arg -> specifier == 'd') || (arg -> specifier == 'i')))
	{
		tmp = ft_strjoin("+", arg -> word);
		if (tmp == NULL)
			return (EXIT_FAILURE);
		free(arg -> word);
		arg -> word = tmp;
		arg -> len = ft_strlen(tmp);
	}
	return (EXIT_SUCCESS);
}
