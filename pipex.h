/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/21 22:40:49 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# define PROCESS_NUM 2
# define PIPE_NUM 2

typedef struct s_arg_lst {
    char    **str;
    int   input_fd;
    int   output_fd;
    struct s_arg_lst *next;
} t_arg_lst;

// typedef struct s_data {
// } t_data;

#endif