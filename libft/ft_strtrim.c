/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:54:40 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/15 01:36:06 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// 1. Loop Over the left hand side of string "s1" by 'i'
// 2.   Looking for keyword "set"
// 3.    update until does not found keyword and save as a start

// 4. Loop Over the right hand side of string "s1" by 'j'
// 5.   Looking for keyword "set"
// 6.    update until does not found keyword and save as a end

// 7. Use word = ft_string("s1", start, end - start) to get the word
// 8. Return "word"

static int	check_keyword(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*word;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start <= end)
	{
		if (!(check_keyword(s1[start], set)))
			break ;
		start++;
	}
	while ((int)end >= 0)
	{
		if (!(check_keyword(s1[end], set)))
			break ;
		end--;
	}
	word = ft_substr(s1, start, end - start + 1);
	return (word);
}
