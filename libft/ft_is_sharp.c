/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sharp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:00:28 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sharp(t_arg *arg)
{
	char	*tmp;

	if (arg -> hash && ((arg -> specifier == 'x') || (arg -> specifier == 'X')))
	{
		if (!(arg -> isnull))
		{
			if (arg -> specifier == 'x')
				tmp = ft_strjoin("0x", arg -> word);
			else
				tmp = ft_strjoin("0X", arg -> word);
			if (tmp == NULL)
				return (EXIT_FAILURE);
			free(arg -> word);
			arg -> word = tmp;
			arg -> len = ft_strlen(tmp);
		}
	}
	return (EXIT_SUCCESS);
}
