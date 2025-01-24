/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:11:07 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/24 17:53:06 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_parent_process(t_data *data_ptr, t_arg_lst *lst, char **path)
{
    close((*data_ptr).pipe_fd[1]);
    if ((*data_ptr).count > 0)
        close((*data_ptr).old_read_fd);
    if ((*data_ptr).count < PROCESS_NUM - 1)
    {
        (*data_ptr).old_read_fd = dup((*data_ptr).pipe_fd[0]);
        if ((*data_ptr).old_read_fd == -1)
        {
            perror("dup");
            ft_clear_data(lst, path);
            exit(1);
        }
        close((*data_ptr).pipe_fd[0]);
    }
}