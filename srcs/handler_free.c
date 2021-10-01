/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:17:45 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/03 18:10:01 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 130;
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	free_line_data_part(t_data *data)
{
	if (data->cmds)
		ft_freearray((void **)data->cmds);
	data->cmds = NULL;
	if (data->argvs)
		ft_freearray2((void ***)data->argvs);
	data->argvs = NULL;
	if (data->redirs)
		ft_freearray2((void ***)data->redirs);
	data->redirs = NULL;
	if (data->fds)
		close_fds(data);
	if (data->fds)
		free(data->fds);
	data->fds = NULL;
	if (data->pipes)
		free(data->pipes);
	data->pipes = NULL;
}

void	free_line_data(t_data *data)
{
	if (data->cwd)
		free(data->cwd);
	data->cwd = NULL;
	if (data->ps1)
		free(data->ps1);
	data->ps1 = NULL;
	if (data->ps2)
		free(data->ps2);
	data->ps2 = NULL;
	if (data->line)
		free(data->line);
	data->line = NULL;
	free_line_data_part(data);
}

void	free_init_data(t_data *data)
{
	rl_clear_history();
	if (data->env)
		ft_freearray((void **)data->env);
	data->env = NULL;
	if (data->builtins)
		free_builtins(data->builtins);
	data->builtins = NULL;
	if (data)
		free(data);
	data = NULL;
}
