/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:05:50 by thacharo          #+#    #+#             */
/*   Updated: 2024/09/04 19:36:27 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*word;

	i = 0;
	word = (char *)s;
	while (i < ft_strlen(s) + 1)
	{
		if (word[i] == (char)c)
			return (&word[i]);
		i++;
	}
	return (NULL);
}
