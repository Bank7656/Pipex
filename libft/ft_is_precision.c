/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:06:23 by thacharo          #+#    #+#             */
/*   Updated: 2024/11/26 13:25:58 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			update_arg(t_arg *arg, char **tmp);
static int		number_precision(t_arg *arg, char **tmp);
static int		string_precision(t_arg *arg, char **tmp);

int	ft_is_precision(t_arg *arg)
{
	int		status;
	char	*tmp;

	tmp = NULL;
	status = EXIT_SUCCESS;
	if (arg -> precision == -1)
		return (EXIT_SUCCESS);
	else if (arg -> specifier == 's' && arg -> len > arg -> precision)
		status = string_precision(arg, &tmp);
	else if (arg -> specifier == 'd' || arg -> specifier == 'i'
		|| arg -> specifier == 'u' || arg -> specifier == 'x'
		|| arg -> specifier == 'X')
	{
		if (arg -> len <= arg -> precision)
			status = number_precision(arg, &tmp);
		else if (arg->word[0] == '0' && arg->len == 1 && arg->precision == 0)
		{
			arg -> word[0] = 0;
			arg -> len = 0;
			return (EXIT_SUCCESS);
		}
	}
	if (status)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	number_precision(t_arg *arg, char **tmp)
{
	int	i;

	if (arg -> word[0] == '-')
		i = arg -> precision + 2;
	else
		i = arg -> precision + 1;
	*tmp = (char *)ft_calloc(i, sizeof(char));
	if (*tmp == NULL)
		return (EXIT_FAILURE);
	ft_memset(*tmp, '0', i - 1);
	ft_strlcpy(*tmp + (i - 1) - arg -> len, arg -> word, arg -> len + 1);
	if (arg -> word[0] == '-')
	{
		(*tmp)[0] = '-';
		(*tmp)[(i - 1) - arg -> len] = '0';
	}
	update_arg(arg, tmp);
	return (EXIT_SUCCESS);
}

static int	string_precision(t_arg *arg, char **tmp)
{
	if (arg -> isnull == 1 && __LINUX__)
	{
		(*tmp) = ft_strdup("");
		if (*tmp == NULL)
			return (EXIT_FAILURE);
		update_arg(arg, tmp);
	}
	(*tmp) = ft_substr(arg -> word, 0, arg -> precision);
	if (*tmp == NULL)
		return (EXIT_FAILURE);
	update_arg(arg, tmp);
	return (EXIT_SUCCESS);
}

void	update_arg(t_arg *arg, char **tmp)
{
	free(arg -> word);
	arg -> word = *tmp;
	arg -> len = ft_strlen(arg -> word);
}
