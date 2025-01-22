/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/22 17:50:17 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# define PROCESS_NUM 2
# define PIPE_NUM 2

typedef struct s_arg_lst {
    char    **str;
    struct s_arg_lst *next;
} t_arg_lst;

typedef struct s_data {
    int  count;
    int  input_fd;
    int  output_fd;
    int  pipe_fd[PIPE_NUM];
    int  old_read_fd;
    char *infile_name;
    char *outfile_name;
    char *program_path;
} t_data;

#endif