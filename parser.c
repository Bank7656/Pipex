/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:13:33 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/24 17:30:40 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_arg_lst *ft_check_argv(char **argv)
{
    int i;
    t_arg_lst   *lst;
    char    **words;

    i = 2;
    lst = (t_arg_lst *)malloc(sizeof(t_arg_lst));
    if (lst == NULL)
    {
        ft_clear_data(lst, NULL);
        exit(1);
    }
    lst -> str = NULL;
    lst -> next = NULL;
    while (argv[i + 1] != NULL)
    {
        create_lst(&lst, argv[i]);
        i++;
    }
    return (lst);
}

char **ft_check_envp(t_arg_lst **lst, char **envp)
{
    int     i;
    char    *str;
    char    **return_str;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
        {
            str = ft_strtrim(envp[i], "PATH=");
            if (str == NULL)
            {
                ft_clear_data(*lst, NULL);
                exit(1);
            }
            return_str = ft_split(str, ':');
            free(str);
            if (return_str == NULL)
            {
                ft_clear_data(*lst, NULL);
                exit(1);
            }
            return (return_str);
        }
        i++;
    }
    return (NULL);
}