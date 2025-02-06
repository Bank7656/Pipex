/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:06:39 by thacharo          #+#    #+#             */
/*   Updated: 2024/10/12 11:46:05 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t		i;
// 	char	*str;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	i = -1;
// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	str = (char *)malloc((sizeof(char) * (s1_len + s2_len + 1)));
// 	if (str == NULL)
// 			return (NULL);
// 	while (++i < s1_len)
// 		str[i] = s1[i];
// 	while(i < (s1_len + s2_len))
// 	{
// 		str[i] = s2[i - s2_len];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	s1_len;
// 	size_t	s2_len;

// 	if (s1 == NULL || s2 == NULL)
// 		return (NULL);
// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	str = (char *)malloc((sizeof(char) * (s1_len + s2_len)) + 1);
// 	if (str == NULL)
// 		return (NULL);
// 	ft_strlcpy(str, s1, s1_len + 1);
// 	ft_strlcat(str, s2, (s1_len + s2_len) + 1);
// 	return (str);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc((sizeof(char) * (s1_len + s2_len + 1)));
	if (str == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[++j] != '\0')
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}
