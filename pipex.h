/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/15 01:16:45 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

typedef struct s_arg_lst {
    char **str;
    struct s_arg_lst *next;
} t_arg_lst;

// typedef struct s_data {
// } t_data;

#endif