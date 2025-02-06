/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 00:51:09 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_percent(t_arg *arg)
{
	arg -> len = 1;
	arg -> word = (char *)ft_calloc(arg -> len, sizeof(char) + 1);
	if (arg -> word == NULL)
		return (EXIT_FAILURE);
	arg -> word[0] = '%';
	arg -> word[1] = '\0';
	return (EXIT_SUCCESS);
}
