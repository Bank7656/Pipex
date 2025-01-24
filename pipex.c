/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:53 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/24 17:54:36 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_execution(t_data data, t_arg_lst *lst, char **path, char **envp);

int main(int argc, char *argv[], char *envp[])
{
    t_data      data;
    t_arg_lst   *lst;
    char    **env_path;

    if (argc != 5)
        return (128);     
    data.count = 0;
    data.infile_name = argv[1];
    data.outfile_name = argv[argc - 1];
    lst = ft_check_argv(argv);
    env_path = ft_check_envp(&lst, envp);
    if (env_path == NULL)
    {
        ft_clear_data(lst, env_path);
        exit(1);
    }
    data.input_fd = open(data.infile_name, O_RDONLY);
    if (data.input_fd == -1)
    {
        ft_clear_data(lst, env_path);
        return (1);
    }
    ft_execution(data, lst, env_path, envp);
    ft_clear_data(lst, env_path);
    return (0);
}

void    ft_clear_data(t_arg_lst *lst, char **path)
{
    int i;
    int j;
    t_arg_lst *tmp;
    while (lst != NULL)
    {
        tmp = lst;
        lst = lst -> next;
        i = -1;
        while (tmp -> str[++i] != NULL)
            free(tmp -> str[i]);
        free(tmp -> str);
        free(tmp);
    }
    i = 0;
    if (path != NULL)
    {
        while (path[i] != NULL)
        {
            free(path[i]);
            i++;
        }
        free(path);
    }
}

void    ft_execution(t_data data, t_arg_lst *lst, char **path, char **envp)
{
    int status;
    pid_t pid;
    pid_t w_pid;

    dup2(data.input_fd, STDIN_FILENO);
    while (data.count < PROCESS_NUM)
    {
        if (pipe(data.pipe_fd) == -1)
        {
            perror("pipe"); 
            ft_clear_data(lst, path);
            exit(1);
        }
        pid = ft_fork(lst, path);
        if (pid == 0)
            ft_child_process(&data, lst, path, envp);
        data.parent_id[data.count] = pid;
        ft_parent_process(&data, lst, path);
        lst = lst -> next;
        data.count++;  
    }
    while (data.count > 0)
    {
        w_pid = waitpid(data.parent_id[data.count - 1], &status, 0);
        if (w_pid < 0)
        {
            perror("Error");
            ft_clear_data(lst, path);
        }
        data.count--;
    }
}