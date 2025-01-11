/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:08:22 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:22:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_get_flag(t_arg *arg, char c)
{
	if (c == '-')
		arg -> minus = 1;
	else if (c == '0')
		arg -> zero = 1;
	else if (c == '#')
		arg -> hash = 1;
	else if (c == ' ')
		arg -> space = 1;
	else if (c == '+')
		arg -> plus = 1;
}
