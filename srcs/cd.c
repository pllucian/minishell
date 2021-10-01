/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 22:51:29 by pllucian          #+#    #+#             */
/*   Updated: 2021/09/30 22:52:09 by pllucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_update_env(char **cwd, char **env)
{
	char	**old_pwd;
	char	**new_pwd;
	char	*tmp;

	old_pwd = get_ptr_var_env(env, "OLDPWD");
	if (old_pwd)
	{
		free(*old_pwd);
		tmp = ft_strdup("OLDPWD=");
		*old_pwd = ft_strjoin(tmp, *cwd);
		free(tmp);
	}
	free(*cwd);
	*cwd = getcwd(NULL, 0);
	new_pwd = get_ptr_var_env(env, "PWD");
	if (new_pwd)
	{
		free(*new_pwd);
		tmp = ft_strdup("PWD=");
		*new_pwd = ft_strjoin(tmp, *cwd);
		free(tmp);
	}
}

int	cd_path(char **cwd, char **env, char *path)
{
	char	*msg;

	if (chdir(path))
	{
		msg = ft_strjoin("minishell: cd: ", path);
		perror(msg);
		free(msg);
		free(path);
		return (EXIT_FAILURE);
	}
	free(path);
	cd_update_env(cwd, env);
	return (EXIT_SUCCESS);
}

int	func_cd(void *data, int i)
{
	char	**cwd;
	char	**argv;
	char	**env;
	char	*path;

	cwd = &(((t_data *)data)->cwd);
	argv = ((t_data *)data)->argvs[i];
	env = ((t_data *)data)->env;
	if (ft_arraylen((void **)argv) > 2)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	if (!argv[1])
	{
		path = get_value_env(env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (EXIT_FAILURE);
		}
	}
	else
		path = ft_strdup(argv[1]);
	return (cd_path(cwd, env, path));
}
