/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:51:46 by thacharo          #+#    #+#             */
/*   Updated: 2024/10/13 16:07:51 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cp;

	if (s == NULL)
		return (NULL);
	cp = (char *)malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (cp == NULL)
		return (NULL);
	ft_strlcpy(cp, s, (ft_strlen(s) + 1));
	return (cp);
}
