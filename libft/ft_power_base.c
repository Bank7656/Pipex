/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:00:24 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 12:33:22 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_power(int base, int n)
{
	if (n < 0)
		return (0);
	if (base == 0 || n == 0)
		return (1);
	return (base * ft_power(base, n - 1));
}
