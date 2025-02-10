/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:04:41 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/10 19:26:57 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int ft_is_only_space(char *str);
static char	*get_full_command_path(t_pipex *data, char *cmd);

void	parser(t_pipex *data, char *str)
{
	if (str[0] == 0 || ft_is_only_space(str))
		handle_error(data, "empty string");
	data -> cmds_arg = ft_split(str, ' ');
	if (data -> cmds_arg == NULL)
		handle_error(data, "malloc");
	if (ft_strchr(data -> cmds_arg[0], '/') == NULL)
		data -> command_path = get_full_command_path(data, data -> cmds_arg[0]);
	else
	{
		int	access_check;

		data -> command_path = ft_strdup(data -> cmds_arg[0]);
		access_check = access(data -> command_path, X_OK | F_OK);
		if (errno == PERMISSION_DENIED)
			handle_error(data, "permission denied");
		if (access_check == -1)
			handle_error(data, "no such file");
	}
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
	
	if (data -> env_path == NULL)
		handle_error(data, "access");
	else if (data -> envp == NULL)
		handle_error(data, "no env");
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
		if (errno == 126)
			handle_error(data, "permission denied");
		else if (errno == 127)
			handle_error(data, "access");
		i++;
		free(cmd_path);
	}
	handle_error(data, "access");
	return (NULL);
}

static int ft_is_only_space(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != 0)
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
