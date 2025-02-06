/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:46:10 by thacharo          #+#    #+#             */
/*   Updated: 2024/09/04 19:30:38 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*mem_s1;
	unsigned char	*mem_s2;

	i = 0;
	mem_s1 = (unsigned char *)s1;
	mem_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (mem_s1[i] != mem_s2[i])
			return (mem_s1[i] - mem_s2[i]);
		i++;
	}
	return (0);
}
