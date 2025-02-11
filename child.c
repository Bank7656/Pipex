/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:08:01 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/11 19:57:50 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	dup_input_fd(t_pipex data, int i);
static void	dup_output_fd(t_pipex data, int i);

void	child_process(t_pipex data, char *argv_i, int i)
{
	dup_input_fd(data, i);
	dup_output_fd(data, i);
	parser(&data, argv_i);
	if (execve(data.command_path, data.cmds_arg, data.envp) == -1)
		handle_error(&data, "execve");
	handle_error(&data, "execve");
}

static void	dup_input_fd(t_pipex data, int i)
{
	int	infile_fd;

	if (i == 0)
	{
		infile_fd = open(data.infile, O_RDONLY);
		if (infile_fd == -1)
		{
			close(data.pfd[0]);
			close(data.pfd[1]);
			handle_error(&data, "open");
		}
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			handle_error(&data, "dup2");
		close(infile_fd);
	}
	else
	{
		if (dup2(data.prev_pfd, STDIN_FILENO) == -1)
			handle_error(&data, "dup2");
		close(data.prev_pfd);
	}
	close(data.pfd[0]);
}

static void	dup_output_fd(t_pipex data, int i)
{
	int	outfile_fd;
	int	outfile_options;

	outfile_options = O_WRONLY | O_CREAT | O_TRUNC;
	if (i == data.process_count - 1)
	{
		close(data.pfd[1]);
		outfile_fd = open(data.outfile, outfile_options, 0644);
		if (outfile_fd == -1)
			handle_error(&data, "open");
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
			handle_error(&data, "dup2");
		close(outfile_fd);
	}
	else
	{
		if (dup2(data.pfd[1], STDOUT_FILENO) == -1)
			handle_error(&data, "dup2");
		close(data.pfd[1]);
	}
}
