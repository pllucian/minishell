/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 11:29:19 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/30 23:52:49 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freearray(void **array)
{
	void	**tmp;

	if (!array)
		return ;
	tmp = array;
	while (*tmp)
	{
		free(*tmp);
		*tmp++ = NULL;
	}
	free(array);
}

void	ft_freearray2(void ***array2)
{
	void	***tmp;

	if (!array2)
		return ;
	tmp = array2;
	while (*tmp)
	{
		ft_freearray(*tmp);
		*tmp++ = NULL;
	}
	free(array2);
}

void	free_builtins(t_builtin *builtins)
{
	t_builtin	*tmp;

	if (!builtins)
		return ;
	tmp = builtins;
	while (tmp->cmd)
	{
		free(tmp->cmd);
		tmp->cmd = NULL;
		tmp++;
	}
	free(builtins);
}

void	close_fds(t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->num_cmds)
	{
		if (data->fds[i].fd_read)
			close(data->fds[i].fd_read);
		if (data->fds[i].fd_write)
			close(data->fds[i].fd_write);
	}
}
