/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:04:41 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/11 20:12:31 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_is_only_space(char *str);
static int	check_access(t_pipex *data, char *path);
static char	*get_full_command_path(t_pipex *data, char *cmd);

void	parser(t_pipex *data, char *str)
{
	int	access_check;

	if (str[0] == 0 || ft_is_only_space(str))
		handle_error(data, "empty string");
	data -> cmds_arg = ft_split(str, ' ');
	if (data -> cmds_arg == NULL)
		handle_error(data, "malloc");
	if (ft_strchr(data -> cmds_arg[0], '/') == NULL)
		data -> command_path = get_full_command_path(data, data -> cmds_arg[0]);
	else
	{
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
	char	*tmp;
	char	*cmd_path;

	i = 0;
	if (data -> env_path == NULL)
		handle_error(data, "access");
	while (data -> env_path[i] != NULL)
	{
		tmp = ft_strjoin(data -> env_path[i], "/");
		if (tmp == NULL)
			handle_error(data, "malloc");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (cmd_path == NULL)
			handle_error(data, "malloc");
		if (check_access(data, cmd_path) == 0)
			return (cmd_path);
		i++;
		free(cmd_path);
	}
	handle_error(data, "access");
	return (NULL);
}

static int	check_access(t_pipex *data, char *path)
{
	int	access_check;

	access_check = access(path, X_OK | F_OK);
	if (errno == 126)
		handle_error(data, "permission denied");
	else if (errno == 127)
		handle_error(data, "access");
	return (access_check);
}

static int	ft_is_only_space(char *str)
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
