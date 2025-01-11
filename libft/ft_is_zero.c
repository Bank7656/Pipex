/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:23:09 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	zero_number(t_arg *arg)
{
	char	*tmp;

	if (arg -> specifier == 'd' || arg -> specifier == 'i')
	{
		if (arg -> word[0] == '-' || arg -> word[0] == '+')
			write(1, arg -> word, 1);
		tmp = ft_strtrim(arg -> word, "-+");
		if (tmp == NULL)
			return (EXIT_FAILURE);
		free(arg -> word);
		arg -> word = tmp;
	}
	return (EXIT_SUCCESS);
}

int	zero_hex(t_arg *arg)
{
	char	*tmp;

	if ((arg -> specifier == 'x' || arg -> specifier == 'X')
		&& arg -> hash && !(arg -> isnull))
	{
		if (arg -> word[0] == '0')
			write(1, arg -> word, 2);
		tmp = ft_substr(arg -> word, 2, arg -> len - 2);
		if (tmp == NULL)
			return (EXIT_FAILURE);
		free(arg -> word);
		arg -> word = tmp;
	}
	return (EXIT_SUCCESS);
}

int	zero_space(t_arg *arg)
{
	char	*tmp;

	if (arg -> space)
	{
		if (arg -> word[0] == ' ')
		{
			write(1, " ", 1);
			tmp = ft_strtrim(arg -> word, " ");
			if (tmp == NULL)
				return (EXIT_FAILURE);
			free(arg -> word);
			arg -> word = tmp;
		}
	}
	return (EXIT_SUCCESS);
}
