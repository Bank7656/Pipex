/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:31:52 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/11 19:02:52 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipex(t_pipex *data, char *argv[]);
int		wait_loop(t_pipex *data);
void	create_temp_file(t_pipex *data);

/* ./pipex infile cmd1 cmd2 outfile */
int	main(int argc, char *argv[], char *envp[])
{
	int		status;
	t_pipex	data;

	if (argc < 5)
		return (EXIT_FAILURE);
	else if (argc == 5 && (ft_strncmp(argv[1], "here_doc", 8) == 0))
		return (EXIT_FAILURE);
	else if (argc >= 6 && (ft_strncmp(argv[1], "here_doc", 8) == 0))
		data.is_here_doc = 1;
	else
		data.is_here_doc = 0;
	get_data(argc, argv, envp, &data);
	if (data.is_here_doc)
		create_temp_file(&data);
	pipex(&data, argv);
	status = wait_loop(&data);
	if (data.is_here_doc)
	{
		if (unlink(TEMP_FILE) == -1)
			handle_error(&data, "unlink");
	}
	free_struct(&data);
	return (status);
}

void	create_temp_file(t_pipex *data)
{
	int		temp_fd;
	char	*line;

	temp_fd = open(TEMP_FILE, O_CREAT | O_WRONLY, 0644);
	if (temp_fd == -1)
		handle_error(data, "open");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_putstr_fd("\0", temp_fd);
			free(line);
			break ;
		}
		if (ft_strncmp(line, data -> delimeter, ft_strlen(line) - 1) == 0)
		{
			ft_putstr_fd("\0", temp_fd);
			free(line);
			break ;
		}
		ft_putstr_fd(line, temp_fd);
		free(line);
	}
	close(temp_fd);
}

void	pipex(t_pipex *data, char *argv[])
{
	int	i;
	int	pid;

	i = 1;
	while (i <= data -> process_count)
	{
		if (pipe(data -> pfd) == -1)
			handle_error(data, "pipe");
		pid = fork();
		if (pid == -1)
			handle_error(data, "fork");
		if (pid == 0)
		{
			if (data -> is_here_doc)
				child_process(*data, argv[i + 2], i - 1);
			else
				child_process(*data, argv[i + 1], i - 1);
		}
		else
			parent_process(data, pid, i);
		i++;
	}
}

int	wait_loop(t_pipex *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data -> process_count)
	{
		waitpid(data -> parent_pid[i], &status, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}
