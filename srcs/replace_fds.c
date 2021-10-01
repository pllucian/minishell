/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 18:33:24 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/25 20:19:15 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_fds_pipe(t_data *data, int i)
{
	if (data->num_cmds < 2)
		return ;
	if (i < data->num_cmds - 1)
		pipe(data->pipes[i]);
	if (!i)
	{
		dup2(data->pipes[i][1], STDOUT_FILENO);
		close(data->pipes[i][1]);
	}
	else if (i && i < data->num_cmds - 1)
	{
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
		close(data->pipes[i - 1][0]);
		dup2(data->pipes[i][1], STDOUT_FILENO);
		close(data->pipes[i][1]);
	}
	else
	{
		dup2(data->pipes[i - 1][0], STDIN_FILENO);
		close(data->pipes[i - 1][0]);
	}
}

void	replace_fds_redir(t_data *data, int i)
{
	if (data->fds[i].fd_read)
	{
		dup2(data->fds[i].fd_read, STDIN_FILENO);
		close(data->fds[i].fd_read);
		data->fds[i].fd_read = 0;
	}
	if (data->fds[i].fd_write)
	{
		dup2(data->fds[i].fd_write, STDOUT_FILENO);
		close(data->fds[i].fd_write);
		data->fds[i].fd_write = 0;
	}
}

void	replace_fds(t_data *data, int i)
{
	static int	old_r;
	static int	old_w;

	if (!old_r && !old_w)
	{
		old_r = dup(STDIN_FILENO);
		old_w = dup(STDOUT_FILENO);
		replace_fds_pipe(data, i);
		replace_fds_redir(data, i);
	}
	else
	{
		dup2(old_r, STDIN_FILENO);
		dup2(old_w, STDOUT_FILENO);
		close(old_r);
		close(old_w);
		old_r = 0;
		old_w = 0;
	}
}
