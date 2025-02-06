/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:05:47 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/06 22:29:43 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path(char **env);

void	get_data(int argc, char *argv[], char *envp[], t_pipex *data)
{
	data->process_count = argc - 3;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->cmds_arg = NULL;
	data->command_path = NULL;
	data->envp = envp;
	data->env_path = get_path(envp);
	data->parent_pid = (pid_t *)malloc(sizeof(pid_t) * (data->process_count));
	if (data->parent_pid == NULL)
		handle_error(data, "malloc");
}

static char	**get_path(char **env)
{
	int		i;
	char	**paths;
	char	*trimmed_path;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
		{
			trimmed_path = ft_strtrim(env[i], "PATH=");
			paths = ft_split(trimmed_path, ':');
			free(trimmed_path);
			return (paths);
		}
		i++;
	}
	return (NULL);
}
