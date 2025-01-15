/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:44:06 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/15 01:29:45 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*str;
// 	size_t	string_length;

// 	if (s == NULL)
// 		return (NULL);
// 	string_length = ft_strlen(s);
// 	if (string_length < start)
// 		return (ft_strdup(""));
// 	if (len > string_length - start)
// 		len = string_length - start;
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (str == NULL)
// 		return (str);
// 	ft_strlcpy(str, s + start, len + 1);
// 	return (str);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	char		*tmp;
	size_t		i;
	size_t		string_length;

	tmp = (void *)ft_calloc(1, 1);
	if (tmp == NULL)
		return (NULL);
	if (s == NULL)
		return (tmp);
	string_length = ft_strlen(s);
	if (string_length < start)
		return (tmp);
	free(tmp);
	if (len > string_length - start)
		len = string_length - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
