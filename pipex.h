/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:54:59 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/24 17:56:09 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>

# include "libft/libft.h"

# define PROCESS_NUM 2
# define PIPE_NUM 2

typedef struct s_arg_lst {
	int     is_full_path;
	char    **str;
	char    *full_cmd;
	char	*program_path;
	struct s_arg_lst *next;
} t_arg_lst;

typedef struct s_data {
	int     count;
	int     input_fd;
	int     output_fd;
	int     pipe_fd[PIPE_NUM];
	int     old_read_fd;
	char    *infile_name;
	char    *outfile_name;
	pid_t   parent_id[PROCESS_NUM];
} t_data;

char		**ft_check_envp(t_arg_lst **lst, char **envp);
char		*ft_join_path(t_arg_lst **lst, char **path, char *prog);
char		*ft_get_path(t_arg_lst **lst, char **path);
void		ft_parent_process(t_data *data_ptr, t_arg_lst *lst, char **path);
void		create_lst(t_arg_lst **lst, char *str);
void		ft_clear_data(t_arg_lst *lst, char **path);
void		ft_child_process(t_data *data_ptr, t_arg_lst *lst, char **path, char **envp);
pid_t		ft_fork(t_arg_lst *lst, char **path);
t_arg_lst	*ft_check_argv(char **argv);


#endif