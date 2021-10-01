/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:49:11 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/30 18:27:28 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_cmd_fork(t_data *data, int i, char *cmd)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit(execve(cmd, data->argvs[i], data->env));
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status = WTERMSIG(status) + 128;
	if (g_status == 130)
		ft_putchar_fd('\n', 1);
	if (g_status == 131)
		ft_putendl_fd("Quit", 1);
	signal(SIGINT, &handler);
}

void	launch_cmd(t_data *data, int i)
{
	int		builtin;
	char	*cmd;

	if (!data->argvs[i][0])
		return ;
	replace_fds(data, i);
	builtin = is_builtin(data, data->argvs[i][0]);
	if (builtin >= 0)
		g_status = (*data->builtins[builtin].func)((void *)data, i);
	else
	{
		cmd = get_cmd(data, i);
		if (cmd)
		{
			launch_cmd_fork(data, i, cmd);
			free(cmd);
		}
	}
	replace_fds(data, i);
}

void	launch_cmds(t_data *data)
{
	int		i;

	if (open_redirs(data))
		return ;
	i = -1;
	while (++i < data->num_cmds)
		launch_cmd(data, i);
}
