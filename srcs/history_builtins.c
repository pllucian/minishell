/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 21:21:58 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/01 01:57:48 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_data *data, char *cmd)
{
	int		i;

	i = -1;
	while (++i < NUM_BUILTINS)
	{
		if (!ft_strncmp(cmd, data->builtins[i].cmd, ft_strlen(cmd) + 1))
			return (i);
	}
	return (-1);
}

void	init_builtins(t_data *data)
{
	int		i;

	data->builtins = (t_builtin *)ft_calloc \
		(NUM_BUILTINS + 1, sizeof(t_builtin));
	i = -1;
	data->builtins[++i].cmd = ft_strdup("echo");
	data->builtins[++i].cmd = ft_strdup("cd");
	data->builtins[++i].cmd = ft_strdup("pwd");
	data->builtins[++i].cmd = ft_strdup("export");
	data->builtins[++i].cmd = ft_strdup("unset");
	data->builtins[++i].cmd = ft_strdup("env");
	data->builtins[++i].cmd = ft_strdup("exit");
	i = -1;
	data->builtins[++i].func = &func_echo;
	data->builtins[++i].func = &func_cd;
	data->builtins[++i].func = &func_pwd;
	data->builtins[++i].func = &func_export;
	data->builtins[++i].func = &func_unset;
	data->builtins[++i].func = &func_env;
	data->builtins[++i].func = &func_exit;
}

void	ft_add_history(t_data *data)
{
	char	*path;
	char	*value;
	int		fd;

	add_history(data->line);
	value = get_value_env(data->env, "HOME");
	path = ft_strjoin(value, "/.minishell_history");
	free(value);
	fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		free(path);
		return ;
	}
	ft_putendl_fd(data->line, fd);
	close(fd);
	free(path);
}

void	init_history(t_data *data)
{
	char	*path;
	char	*value;
	int		fd;

	value = get_value_env(data->env, "HOME");
	path = ft_strjoin(value, "/.minishell_history");
	free(value);
	fd = open(path, O_RDONLY, 0644);
	if (fd < 0)
	{
		free(path);
		return ;
	}
	while (get_next_line(fd, &data->line))
	{
		add_history(data->line);
		free(data->line);
	}
	free(data->line);
	data->line = NULL;
	close(fd);
	free(path);
}
