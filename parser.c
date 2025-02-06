/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:04:41 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/06 22:31:40 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_full_command_path(t_pipex *data, char *cmd);

void	parser(t_pipex *data, char *str)
{
	if (str[0] == 0)
		handle_error(data, "access");
	data -> cmds_arg = ft_split(str, ' ');
	if (data -> cmds_arg == NULL)
		handle_error(data, "malloc");
	if (ft_strchr(data -> cmds_arg[0], '/') == NULL)
		data -> command_path = get_full_command_path(data, data -> cmds_arg[0]);
	else
		data -> command_path = ft_strdup(data -> cmds_arg[0]);
	if (data -> command_path == NULL)
		handle_error(data, "malloc");
}

static char	*get_full_command_path(t_pipex *data, char *cmd)
{
	int		i;
	int		access_check;
	char	*tmp;
	char	*cmd_path;

	i = 0;
	while (data -> env_path[i] != NULL)
	{
		tmp = ft_strjoin(data -> env_path[i], "/");
		if (tmp == NULL)
			handle_error(data, "malloc");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (cmd_path == NULL)
			handle_error(data, "malloc");
		access_check = access(cmd_path, X_OK | F_OK);
		if (access_check == 0)
			return (cmd_path);
		i++;
		free(cmd_path);
	}
	handle_error(data, "access");
	return (NULL);
}
