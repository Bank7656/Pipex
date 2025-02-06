/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:31:52 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/06 22:30:33 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(t_pipex *data, char *argv[]);
int		wait_loop(t_pipex *data);

/* ./pipex infile cmd1 cmd2 outfile */
int	main(int argc, char *argv[], char *envp[])
{
	int		status;
	t_pipex	data;

	if (argc != 5)
		return (EXIT_FAILURE);
	get_data(argc, argv, envp, &data);
	pipex(&data, argv);
	status = wait_loop(&data);
	free_struct(&data);
	return (status);
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
			child_process(*data, argv[i + 1], i - 1);
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
