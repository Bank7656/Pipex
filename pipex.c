/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:53 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/15 01:17:13 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>
#include <errno.h>

t_arg_lst *ft_check_argv(char **argv);
void    create_lst(t_arg_lst **lst, char *str);
char **ft_check_envp(char **envp);

int main(int argc, char *argv[], char *envp[])
{
    t_arg_lst   *lst;
    char    **env_path;

    if (argc != 5)
        return (1);
     
    lst = ft_check_argv(argv);
    env_path = ft_check_envp(envp);
    t_arg_lst *tmp;
    int     i;

    tmp = lst;
    while (tmp != NULL)
    {
        i = 0;
        while (tmp -> str[i] != NULL)
        {
            printf("%s\n", tmp -> str[i]);
            i++;
        }
        tmp = tmp -> next;
    }
    return (0);
}

t_arg_lst *ft_check_argv(char **argv)
{
    int i;
    int j;
    t_arg_lst   *lst;
    char    **words;

    i = 2;
    lst = (t_arg_lst *)malloc(sizeof(t_arg_lst));
    if (lst == NULL)
        exit(0);
    lst -> str = NULL;
    lst -> next = NULL;
    while (argv[i + 1] != NULL)
    {
        create_lst(&lst, argv[i]);
        // words = ft_split(argv[i], ' ');
        // if (words == NULL)
        //     return (1);
        i++;
    }
    return (lst);
}

void    create_lst(t_arg_lst **lst, char *str)
{
    t_arg_lst *tmp;
    t_arg_lst *trav;
    char    **words;

    words = ft_split(str, ' ');
    if (words == NULL)
    {
        // free lst
        exit(0);
    }
    trav = (*lst);
    if (trav -> str == NULL)
        trav -> str = words;
    else
    {    
        tmp = (t_arg_lst *)malloc(sizeof(t_arg_lst));
        if (tmp == NULL)
        {
            // free lst
            exit(0);
        }
        tmp -> str = words;
        while (trav -> next != NULL)
            trav = trav -> next;
        trav -> next = tmp;
    }
}

char **ft_check_envp(char **envp)
{
    int i;
    char *str;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
        {
            str = ft_strtrim(envp[i], "PATH=");
            // str = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
            if (str == NULL)
                exit(0);
            return (ft_split(str, ':'));
        }
        i++;
    }
    
    return (NULL);
}
