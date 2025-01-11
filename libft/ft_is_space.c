/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:18:15 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_space(t_arg *arg)
{
	char	*tmp;

	if (arg -> space && ((arg -> word[0] != '-'))
		&& ((arg -> specifier == 'd') || (arg -> specifier == 'i')))
	{
		if (arg -> word[0] == 0)
		{
			tmp = ft_strdup(" ");
			if (tmp == NULL)
				return (EXIT_FAILURE);
			update_arg(arg, &tmp);
		}
		else if (arg -> len != 0)
		{
			tmp = ft_strjoin(" ", arg -> word);
			if (tmp == NULL)
				return (EXIT_FAILURE);
			update_arg(arg, &tmp);
		}
	}
	return (EXIT_SUCCESS);
}
