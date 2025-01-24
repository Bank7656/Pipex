/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:12:29 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/24 17:55:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void    ft_is_full_path(t_arg_lst **lst);

pid_t    ft_fork(t_arg_lst *lst, char **path)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        ft_clear_data(lst, path);
        exit(1);
    }
    return (pid);
}

void    create_lst(t_arg_lst **lst, char *str)
{
    t_arg_lst *tmp;
    t_arg_lst *trav;
    char    **words;

    words = ft_split(str, ' ');
    if (words == NULL)
    {
        ft_clear_data(*lst, NULL);
        exit(1);
    }
    trav = (*lst);
    if (trav -> str == NULL)
        trav -> str = words;
    else
    {
        tmp = (t_arg_lst *)malloc(sizeof(t_arg_lst));
        if (tmp == NULL)
        {
            ft_clear_data(*lst, NULL);
            exit(1);
        }
        tmp -> next = NULL;
        tmp -> str = words;
        while (trav -> next != NULL)
            trav = trav -> next;
        trav -> next = tmp;
        trav = trav -> next;
    }
    trav -> full_cmd = str;
    trav -> program_path = NULL;
    trav -> next = NULL; 
    ft_is_full_path(&trav);
}

static void    ft_is_full_path(t_arg_lst **lst)
{
    t_arg_lst *tmp;

    tmp = *lst;
    if (ft_strchr(tmp -> full_cmd, '/') != NULL)
        tmp -> is_full_path = 1;
    else
        tmp -> is_full_path = 0;     
}

char    *ft_get_path(t_arg_lst **lst, char **path)
{
    t_arg_lst *ptr;

    ptr = *lst;
    if (ptr -> is_full_path)
    {
        if (access(ptr -> str[0], X_OK | F_OK) == 0)
            return (ptr -> str[0]);
        else
        {
            perror(ptr -> str[0]);
            ft_clear_data(ptr, path);
            exit(127);
        }
    }
    else
        return (ft_join_path(lst, path, ptr -> str[0]));    
}

char    *ft_join_path(t_arg_lst **lst, char **path, char *prog)
{
    int     i;
    char    *tmp;
    char    *full_path;

    i = 0;
    while (path[i] != NULL)
    {
        tmp = ft_strjoin(path[i], "/");
        full_path = ft_strjoin(tmp, prog);
        free(tmp);
        if (full_path == NULL)
        {
            ft_clear_data(*lst, path);
            exit(1);
        }
        if (access(full_path, X_OK | F_OK) == 0)
            return (full_path);
        i++;
    }
    return (NULL);
}