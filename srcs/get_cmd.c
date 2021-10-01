/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 22:00:02 by pllucian          #+#    #+#             */
/*   Updated: 2021/10/01 03:38:48 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char **argv, char *path)
{
	struct dirent	*entry;
	DIR				*dir;
	char			*cmd;
	char			*tmp;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ft_strncmp(argv[0], entry->d_name, ft_strlen(argv[0]) + 1) \
			&& ft_strncmp(argv[0], "..", 3))
		{
			closedir(dir);
			tmp = ft_strjoin(path, "/");
			cmd = ft_strjoin(tmp, argv[0]);
			free(tmp);
			return (cmd);
		}
	}
	closedir(dir);
	return (NULL);
}

char	*get_cmd_paths(char **argv, char **env)
{
	char	**paths;
	char	*value;
	char	*cmd;
	int		i;

	value = get_value_env(env, "PATH");
	paths = ft_split(value, ':');
	if (value)
		free(value);
	i = -1;
	while (paths && paths[++i])
	{
		cmd = get_cmd_path(argv, paths[i]);
		if (cmd)
		{
			ft_freearray((void **)paths);
			return (cmd);
		}
	}
	ft_freearray((void **)paths);
	g_status = 127;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putendl_fd(": command not found", 2);
	return (NULL);
}

char	*get_cmd_source(char **argv)
{
	if (!argv[1])
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
	}
	else
	{
		g_status = 1;
		ft_putstr_fd("minishell: .: source is a builtin command", 2);
	}
	return (NULL);
}

char	*get_cmd(t_data *data, int i)
{
	char	***argv;
	char	**env;

	argv = &(data->argvs[i]);
	env = data->env;
	if (!ft_strncmp((*argv)[0], ".", 2))
		return (get_cmd_source(*argv));
	else if (ft_strchr((*argv)[0], '/'))
		return (get_cmd_file(argv, env));
	return (get_cmd_paths(*argv, env));
}
