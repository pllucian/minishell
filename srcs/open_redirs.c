/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 13:47:27 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/28 17:25:05 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_output(t_data *data, char *redir, int i)
{
	char	*msg;

	redir += 1;
	while (ft_isspace(*redir))
		redir++;
	data->fds[i].fd_write = open \
		(redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fds[i].fd_write < 0)
	{
		g_status = 1;
		msg = ft_strjoin("minishell: ", redir);
		perror(msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_redir_input(t_data *data, char *redir, int i)
{
	char	*msg;

	redir += 1;
	while (ft_isspace(*redir))
		redir++;
	data->fds[i].fd_read = open(redir, O_RDONLY, 0644);
	if (data->fds[i].fd_read < 0)
	{
		g_status = 2;
		msg = ft_strjoin("minishell: ", redir);
		perror(msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_redir_output_append(t_data *data, char *redir, int i)
{
	char	*msg;

	redir += 2;
	while (ft_isspace(*redir))
		redir++;
	data->fds[i].fd_write = open \
		(redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fds[i].fd_write < 0)
	{
		g_status = 1;
		msg = ft_strjoin("minishell: ", redir);
		perror(msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_redir(t_data *data, char *redir, int i)
{
	if (!ft_strncmp(redir, "<<", 2))
	{
		if (heredoc(data, redir, i))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(redir, ">>", 2))
	{
		if (open_redir_output_append(data, redir, i))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(redir, "<", 1))
	{
		if (open_redir_input(data, redir, i))
			return (EXIT_FAILURE);
	}
	else if (!ft_strncmp(redir, ">", 1))
	{
		if (open_redir_output(data, redir, i))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	open_redirs(t_data *data)
{
	int		i;
	int		j;

	i = -1;
	while (data->redirs[++i])
	{
		j = -1;
		while (data->redirs[i][++j])
		{
			if (open_redir(data, data->redirs[i][j], i))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
