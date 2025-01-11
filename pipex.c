/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:53 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/12 01:53:02 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_check_envp(char **envp);

int main(int argc, char *argv[], char *envp[])
{
    // if (argc != 5)
    //     return (1);

    if (ft_check_envp(envp))
    {
        printf("PATH not found\n");
        return (1);
    }
    printf("Path founded\n");
    return (0);
}

int ft_check_envp(char **envp)
{
    int i;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
            return (0);
        i++;
    }
    return (1);
}
