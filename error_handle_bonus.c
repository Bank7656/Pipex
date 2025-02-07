/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:09:46 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/07 03:33:28 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
