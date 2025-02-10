/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:18:04 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/10 23:28:04 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define PERMISSION_DENIED 13
# define COMMAND_NOT_FOUND "command not found"
# define TEMP_FILE "temp.txt"

/* perror */
# include <stdio.h>

/* open */
# include <fcntl.h>

/* wait and waitpid */
# include <sys/wait.h>

/* errno */
# include <errno.h>

# include "libft/libft.h"

typedef struct s_pipex
{
	int		is_here_doc;
	int		process_count;
	int		pfd[2];
	int		prev_pfd;
	char	*infile;
	char	*outfile;
	char	*delimeter;
	char	**cmds_arg;
	char	*command_path;
	char	**envp;
	char	**env_path;
	pid_t	*parent_pid;
}	t_pipex;

/* parser.c */
void	parser(t_pipex *data, char *str);

/* getter.c */
void	get_data(int argc, char *argv[], char *envp[], t_pipex *data_ptr);
void	get_temp_file(t_pipex *data);

/* child.c */
void	child_process(t_pipex data, char *argv_i, int i);

/* parent.c */
void	parent_process(t_pipex *data, int pid, int i);

/* error_handle.c */
void	handle_error(t_pipex *data, char *func_name);
void	free_struct(t_pipex *data);

#endif 
