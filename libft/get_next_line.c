/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 02:34:29 by thacharo          #+#    #+#             */
/*   Updated: 2025/01/06 02:45:43 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	int			remain_check;
	char		*line;
	char		*read;
	char		*buffer;
	static char	*remaining;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	read = NULL;
	remain_check = clear_remain(&line, &remaining, read, 0);
	if (remain_check == 0)
		return (line);
	else if (remain_check == -1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(line), NULL);
	read = get_read(&line, &remaining, &buffer, fd);
	free(buffer);
	if (read == NULL)
		return (free(remaining), NULL);
	return (line);
}

char	*get_read(char **line, char **remaining, char **buffer, int fd)
{
	int	check;
	int	read_count;

	check = 1;
	read_count = 1;
	while (read_count > 0)
	{
		read_count = read(fd, *buffer, BUFFER_SIZE);
		if (read_count == -1)
			return (free(*line), NULL);
		(*buffer)[read_count] = '\0';
		get_current_line(line, *buffer);
		if (*line == NULL)
			break ;
		if (*remaining != NULL)
			free(*remaining);
		*remaining = get_remain(remaining, *buffer, &check);
		if (check == -1)
			return (free(*line), NULL);
		if (ft_strchr(*buffer, '\n'))
			break ;
	}
	if (read_count == 0)
		free(*remaining);
	return (*line);
}

void	get_current_line(char **line, char *buffer)
{
	int		count;
	char	*tmp1;
	char	*tmp2;

	count = 0;
	while (buffer[count] != '\0' && buffer[count] != '\n')
		count++;
	if (*line == NULL)
	{
		*line = ft_substr(buffer, 0, count + 1);
		if (*line == NULL)
			return ;
		if (*line[0] == 0)
		{
			free(*line);
			*line = NULL;
		}
		return ;
	}
	tmp1 = ft_substr(buffer, 0, count + 1);
	tmp2 = ft_strjoin(*line, tmp1);
	free(*line);
	free(tmp1);
	*line = tmp2;
}

char	*get_remain(char **remain, char *buffer, int *remain_check)
{
	int		count;
	char	*tmp;

	count = 0;
	while (buffer[count] != '\0' && buffer[count] != '\n')
		count++;
	if (*remain != NULL)
	{
		free(*remain);
		*remain = NULL;
	}
	if (buffer[count] == '\n')
		tmp = ft_substr(buffer, count + 1, BUFFER_SIZE - count);
	else
		return (NULL);
	if (tmp == NULL)
	{
		*remain_check = -1;
		return (free(tmp), NULL);
	}
	if (tmp[0] == 0)
		return (free(tmp), NULL);
	return (tmp);
}

int	clear_remain(char **line, char **remain, char *tmp, int count)
{
	if (*remain == NULL)
		return (1);
	while ((*remain)[count] != '\0' && (*remain)[count] != '\n')
		count++;
	*line = ft_substr(*remain, 0, count + 1);
	if (*line == NULL)
	{
		free(*remain);
		*remain = NULL;
		return (-1);
	}
	tmp = ft_substr(*remain, count + 1, BUFFER_SIZE - count);
	free(*remain);
	*remain = NULL;
	if (tmp == NULL)
		return (free(*line), -1);
	if (tmp[0] == 0)
		return (free(tmp), 1);
	*remain = tmp;
	return (0);
}
