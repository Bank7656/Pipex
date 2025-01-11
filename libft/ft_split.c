/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:04:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/06 14:25:23 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int		count;
	size_t	i;
	size_t	len;

	i = 0;
	count = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		while (s[i] != c)
		{
			i++;
			if (s[i] == c || (s[i] == '\0' && s[i - 1] != c))
			{
				count++;
				break ;
			}
		}
		i++;
	}
	return (count);
}

static void	free_arr(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	split_words(char **arr, char const *s, char c, size_t start)
{
	size_t	i;
	size_t	j;
	size_t	counter;

	i = 0;
	j = 0;
	counter = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] != c)
		{
			if (counter++ == 0)
				start = i;
			i++;
			if (s[i] == c || (s[i] == '\0' && s[i - 1] != c))
			{
				arr[j] = ft_substr(s, start, i - start);
				if (arr[j++] == NULL)
					return (free_arr(arr, j - 1));
				counter = 0;
				break ;
			}
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		num_words;

	if (s == NULL)
		return (NULL);
	num_words = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (words == NULL)
		return (NULL);
	split_words(words, s, c, 0);
	words[num_words] = NULL;
	return (words);
}
