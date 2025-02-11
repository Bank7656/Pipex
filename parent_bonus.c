/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:08:52 by thacharo          #+#    #+#             */
/*   Updated: 2025/02/11 19:00:46 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	parent_process(t_pipex *data, int pid, int i)
{
	if (i > 1)
		close(data -> prev_pfd);
	data -> parent_pid[i - 1] = pid;
	if (i < data->process_count)
	{
		data -> prev_pfd = dup(data -> pfd[0]);
		if (data -> prev_pfd == -1)
			handle_error(data, "dup");
	}
	close(data -> pfd[0]);
	close(data -> pfd[1]);
}
