/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:05:03 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/24 17:53:25 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_child_process(t_data *data_ptr, t_arg_lst *lst, char **path, char **envp)
{
    t_data  data;

    data = *data_ptr;
    lst -> program_path = ft_get_path(&lst, path);    
    if (data.count > 0)
    {
        if (dup2(data.old_read_fd, STDIN_FILENO) == -1)
        {
            perror("dup2()");
            ft_clear_data(lst, path);
            exit(1);
        }
        close(data.old_read_fd);
    }
    close(data.pipe_fd[0]);
    if (data.count == PROCESS_NUM -1)
    {
        data.output_fd = open(data.outfile_name, O_WRONLY | O_CREAT, 0644);
        if (data.output_fd == -1)
        {
            perror("open");
            ft_clear_data(lst, path);
            exit(1);
        }   
        if (dup2(data.output_fd, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            ft_clear_data(lst, path);
            exit(1);
        }
        close(data.output_fd);
    }
    else
    {
        if (dup2(data.pipe_fd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2");
            ft_clear_data(lst, path);
            exit(1);
        }
            
    }
    close(data.pipe_fd[1]);
    if (execve(lst -> program_path, lst -> str, envp) == -1)
    {
        perror("execve");
        ft_clear_data(lst, path);
        exit(126);
    }
}