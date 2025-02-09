/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:09:46 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/10 01:49:06 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(t_pipex *data, char *func_name)
{
	if (ft_strncmp(func_name, "access", -1) == 0)
	{
		if (data -> cmds_arg == NULL)
			ft_putstr_fd(" ", STDERR_FILENO);
		else
			ft_putstr_fd(data -> cmds_arg[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_struct(data);
		if (ft_strncmp(func_name, "access", -1) == 0) 
			exit(127);
	} 
	else if (ft_strncmp(func_name, "permission denied", -1) == 0)
	{
		perror(data -> cmds_arg[0]);
		free_struct(data);
		exit(126);
	}
	else if (ft_strncmp(func_name, "open", -1) == 0)
	{
		perror(data -> outfile);
		free_struct(data);
		exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(func_name, "no such file", -1) == 0)
	{
		perror(data -> cmds_arg[0]);
		free_struct(data);
		exit(127);		
	}
	else if (ft_strncmp(func_name, "no env", -1) == 0)
	{
		free_struct(data);
		exit(127);
	}
	else if (ft_strncmp(func_name, "execve", -1) == 0)
	{
		perror(data -> cmds_arg[0]);
		free_struct(data);
		exit(126);			
	}
	else if (ft_strncmp(func_name, "empty string", -1) == 0)
	{
		ft_putstr_fd(" ", STDERR_FILENO);
		ft_putstr_fd("/: Command not found\n", STDERR_FILENO);
		free_struct(data);
		exit(127);
	}
	else
	{
		free_struct(data);
		perror(func_name);
		exit(EXIT_FAILURE);
	}
}

void	free_struct(t_pipex *data)
{
	int	i;

	free(data -> parent_pid);
	i = 0;
	if (data -> env_path != NULL)
	{
		while (data -> env_path[i] != NULL)
		{
			free(data -> env_path[i]);
			i++;
		}
		free(data -> env_path);
	}
	i = 0;
	if (data -> cmds_arg != NULL)
	{
		while (data -> cmds_arg[i] != NULL)
		{
			free(data -> cmds_arg[i]);
			i++;
		}
		free(data -> cmds_arg);
	}
	if (data -> command_path != NULL)
		free(data -> command_path);
}
