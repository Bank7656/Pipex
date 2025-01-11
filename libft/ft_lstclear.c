/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:29:08 by thacharo          #+#    #+#             */
/*   Updated: 2024/09/04 19:25:11 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	temp = *lst;
	if (*lst == NULL || del == NULL)
	{
		return ;
	}
	while (temp != NULL)
	{
		temp = temp -> next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
