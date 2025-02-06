/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:51:38 by thacharo          #+#    #+#             */
/*   Updated: 2024/10/13 16:06:31 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*word;
	char	*ptr;

	i = 0;
	ptr = NULL;
	word = (char *)s;
	if (s == NULL)
		return (NULL);
	while (i < ft_strlen(s) + 1)
	{
		if (word[i] == (char)c)
			ptr = &word[i];
		i++;
	}
	return (ptr);
}
